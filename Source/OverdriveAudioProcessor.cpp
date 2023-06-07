/*
  ==============================================================================

    OverdriveAudioProcessor.cpp
    Created: 7 Jun 2023 2:47:30pm
    Author:  emmet

  ==============================================================================
*/

#include "OverdriveAudioProcessor.h"
#include "OverdriveAudioProcessorEditor.h"

OverdriveAudioProcessor::OverdriveAudioProcessor()
: apvts (*this, nullptr, "PARAMETERS",
         {std::make_unique<juce::AudioParameterFloat>("input", "Input Gain", -100.0f, 60.0f, 0.0f),
          std::make_unique<juce::AudioParameterFloat>("output", "Output Gain", -100.0f, 60.0f, 0.0f)})
{
}


void OverdriveAudioProcessor::prepareToPlay(double sr, int samplesPerBlock)
{
    sampleRate = sr;
    juce::dsp::ProcessSpec spec { sampleRate, 
                                  static_cast<juce::uint32>(samplesPerBlock), 
                                  static_cast<juce::uint32> (getTotalNumOutputChannels()) };
    updateParameters();

    auto& gainUp = overdrive.get<0>();
    gainUp.setGainDecibels (24);

    auto& bias = overdrive.get<1>();
    bias.setBias (0.4f);

    auto& wavShaper = overdrive.get<2>();
    wavShaper.functionToUse = [](float sample) { return std::tanh(sample); };

    auto& dcFilter = overdrive.get<3>();
    dcFilter.state = juce::dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, 5.0);

    auto& gainDown = overdrive.get<4>();
    gainDown.setGainDecibels (-18.0f);

    overdrive.prepare(spec);
}


void OverdriveAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    updateParameters();
    overdrive.process (context);
}


AudioProcessorEditor* OverdriveAudioProcessor::createEditor() 
{
    return new OverdriveAudioProcessorEditor(*this);
}


void OverdriveAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = apvts.state.createXml())
        copyXmlToBinary(*xml, destData);
}


void OverdriveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary(data, sizeInBytes))
        if (xml->hasTagName(apvts.state.getType()))
            apvts.state = ValueTree::fromXml(*xml);
}


void OverdriveAudioProcessor::updateParameters()
{
    if (sampleRate != 0.0)
    {
        overdrive.get<0>().setGainDecibels (static_cast<float> (*apvts.getRawParameterValue("input")));
        overdrive.get<4>().setGainDecibels (static_cast<float> (*apvts.getRawParameterValue("output")));
    }
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OverdriveAudioProcessor();
}
