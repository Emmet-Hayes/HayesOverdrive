#pragma once
#include "HayesOverdriveAudioProcessor.h"
#include "CustomLookAndFeel.h"
#include "CentredLabel.h"
#include "DbSlider.h"
#include "ScopeComponent.h"
#include "PresetBar.h"

constexpr int NUM_SLIDERS = 3;

class HayesOverdriveAudioProcessorEditor : public juce::AudioProcessorEditor
                                    , private juce::Timer
{
public:
    HayesOverdriveAudioProcessorEditor(HayesOverdriveAudioProcessor& p);

    void paint(juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    void addAllPanelComponents();

    HayesOverdriveAudioProcessor& processor;

    PresetBar presetBar;
    
    std::unique_ptr<ScopeComponent<float>> scopeComponent;
    CustomLookAndFeel customLookAndFeel;
    juce::Image image;

    std::unique_ptr<juce::Slider> sliders[NUM_SLIDERS];
    CentredLabel sliderLabels[NUM_SLIDERS];

    juce::ComboBox waveShapeBox;
    CentredLabel waveShapeLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderAttachments[NUM_SLIDERS];
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveShapeBoxAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HayesOverdriveAudioProcessorEditor)
};
