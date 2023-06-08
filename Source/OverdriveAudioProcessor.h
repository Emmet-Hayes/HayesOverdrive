/*
  ==============================================================================

    OverdriveAudioProcessor.h
    Created: 7 Jun 2023 2:44:57pm
    Author:  emmet

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OverdriveAudioProcessor : public juce::AudioProcessor
{
public:
    OverdriveAudioProcessor();

    void releaseResources() override {}
    const juce::String getName() const override { return "Overdrive"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int /*index*/) override {}
    const juce::String getProgramName(int /*index*/) override { return {}; }
    void changeProgramName(int /*index*/, const juce::String& /*newName*/) override {}
    bool hasEditor() const override { return true; }
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    AudioProcessorEditor* createEditor() override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void updateParameters();
    
    //==============================================================================
    using GainProcessor   = juce::dsp::Gain<float>;
    using BiasProcessor   = juce::dsp::Bias<float>;
    using DriveProcessor  = juce::dsp::WaveShaper<float>;
    using DCFilter        = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                                                juce::dsp::IIR::Coefficients<float>>;

    juce::dsp::ProcessorChain<GainProcessor, BiasProcessor, DriveProcessor, DCFilter, GainProcessor> overdrive;

    juce::AudioProcessorValueTreeState apvts;
    double sampleRate = 0.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OverdriveAudioProcessor)
};

AudioProcessor* JUCE_CALLTYPE createPluginFilter();
