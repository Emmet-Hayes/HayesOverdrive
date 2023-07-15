#pragma once
#include "OverdriveAudioProcessor.h"
#include "CustomLookAndFeel.h"
#include "CentredLabel.h"
#include "DbSlider.h"
#include "ScopeComponent.h"

constexpr int NUM_SLIDERS = 3;

class OverdriveAudioProcessorEditor : public juce::AudioProcessorEditor
                                    , private juce::Timer
{
public:
    OverdriveAudioProcessorEditor(OverdriveAudioProcessor& p);

    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    void addAllPanelComponents();

    OverdriveAudioProcessor& processor;
    
    std::unique_ptr<ScopeComponent<float>> scopeComponent;
    CustomLookAndFeel customLookAndFeel;
    juce::Image image;

    std::unique_ptr<juce::Slider> sliders[NUM_SLIDERS];
    CentredLabel sliderLabels[NUM_SLIDERS];

    juce::ComboBox waveShapeBox;
    CentredLabel waveShapeLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachments[NUM_SLIDERS];
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveShapeBoxAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OverdriveAudioProcessorEditor)
};
