#include "HayesOverdriveAudioProcessor.h"
#include "HayesOverdriveAudioProcessorEditor.h"

HayesOverdriveAudioProcessor::HayesOverdriveAudioProcessor()
:   apvts { *this, nullptr, "PARAMETERS", createParameterLayout() }
{
}


void HayesOverdriveAudioProcessor::prepareToPlay(double sr, int samplesPerBlock)
{
    sampleRate = sr;
    juce::dsp::ProcessSpec spec { sampleRate, 
                                  static_cast<juce::uint32>(samplesPerBlock), 
                                  static_cast<juce::uint32> (getTotalNumOutputChannels()) };
    overdrive.prepare(spec);
    updateParameters();
}


void HayesOverdriveAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midi*/)
{
    updateParameters();
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    overdrive.process(context);

    scopeDataCollector.process(context.getOutputBlock().getChannelPointer(0), context.getOutputBlock().getNumSamples());
}


AudioProcessorEditor* HayesOverdriveAudioProcessor::createEditor() 
{
    return new HayesOverdriveAudioProcessorEditor(*this);
}


void HayesOverdriveAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = apvts.state.createXml())
        copyXmlToBinary(*xml, destData);
}


void HayesOverdriveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary(data, sizeInBytes))
        if (xml->hasTagName(apvts.state.getType()))
            apvts.state = ValueTree::fromXml(*xml);
}


juce::AudioProcessorValueTreeState::ParameterLayout HayesOverdriveAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    layout.add(std::make_unique<juce::AudioParameterFloat>("input", "Input Gain", -36.0f, 36.0f, 0.0f));
    layout.add(std::make_unique<juce::AudioParameterFloat>("bias", "Bias", 0.01f, 0.9f, 0.4f));
    layout.add(std::make_unique<juce::AudioParameterChoice>("waveshape", "Wave Shape", juce::StringArray { "Tanh", "Sin", "Soft", "Hard", "Arctan", "Sigmoid", "Hard Tanh", "Absolute Value"}, 1));
    layout.add(std::make_unique<juce::AudioParameterFloat>("output", "Output Gain", -60.0f, 12.0f, 0.0f));
    return layout;
}

void HayesOverdriveAudioProcessor::updateParameters()
{
    if (sampleRate != 0.0)
    {
        overdrive.get<0>().setGainDecibels(static_cast<float>(*apvts.getRawParameterValue("input")));
        overdrive.get<1>().setBias(static_cast<float>(*apvts.getRawParameterValue("bias")));
        
        auto waveshape = static_cast<int>(*apvts.getRawParameterValue("waveshape"));
        switch (waveshape)
        {
            case 0: overdrive.get<2>().functionToUse = [](float sample) { return std::tanh(sample); }; break;
            case 1: overdrive.get<2>().functionToUse = [](float sample) { return std::sin(sample); }; break;
            case 2: overdrive.get<2>().functionToUse = [](float sample) { return sample > 1.0f ? 0.66f : (sample < -1.0f ? -0.66f : sample - ((sample * sample * sample) / 3)); }; break;
            case 3: overdrive.get<2>().functionToUse = [](float sample) { return sample > 0.8f ? 0.8f : (sample < -0.8f ? -0.8f : sample); }; break;
            case 4: overdrive.get<2>().functionToUse = [](float sample) { return std::atan(sample); }; break;
            case 5: overdrive.get<2>().functionToUse = [](float sample) { return sample > 0.0f ? 1 - std::exp(-sample) : -1 + std::exp(sample); }; break;
            case 6: overdrive.get<2>().functionToUse = [](float sample) { return sample > 0.8f ? std::tanh(sample) : (sample < -0.8f ? std::tanh(sample) : sample); }; break;
            case 7: overdrive.get<2>().functionToUse = [](float sample) { return std::abs(sample); }; break;
            default: overdrive.get<2>().functionToUse = [](float sample) { return std::tanh(sample); };
        }

        auto& dcFilter = overdrive.get<3>();
        dcFilter.state = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 5.0);

        overdrive.get<4>().setGainDecibels(static_cast<float>(*apvts.getRawParameterValue("output")));
    }
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HayesOverdriveAudioProcessor();
}
