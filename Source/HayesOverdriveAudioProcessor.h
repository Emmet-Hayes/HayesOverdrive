#pragma once
#include <JuceHeader.h>
#include "../../Common/BaseAudioProcessor.h"
#include "../../Common/WaveScopeComponent.h"

class HayesOverdriveAudioProcessor : public BaseAudioProcessor
{
public:
    HayesOverdriveAudioProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() override;
    void updateParameters();
    
    using GainProcessor   = juce::dsp::Gain<float>;
    using BiasProcessor   = juce::dsp::Bias<float>;
    using DriveProcessor  = juce::dsp::WaveShaper<float>;
    using DCFilter        = juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>,
                                                juce::dsp::IIR::Coefficients<float>>;

    juce::dsp::ProcessorChain<GainProcessor, BiasProcessor, DriveProcessor, DCFilter, GainProcessor> overdrive;

    double sampleRate = 0.0;

    AudioBufferQueue<float> audioBufferQueue;
    WaveScopeDataCollector<float> scopeDataCollector{ audioBufferQueue };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HayesOverdriveAudioProcessor)
};

AudioProcessor* JUCE_CALLTYPE createPluginFilter();
