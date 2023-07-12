#pragma once
#include "OverdriveAudioProcessor.h"
#include "CustomLookAndFeel.h"
#include "CentredLabel.h"
#include "DbSlider.h"

constexpr int NUM_SLIDERS = 3;

class OverdriveAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    OverdriveAudioProcessorEditor(OverdriveAudioProcessor& p);

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void addAllPanelComponents();

    OverdriveAudioProcessor& processor;
    
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
