#pragma once
#include "HayesOverdriveAudioProcessor.h"
#include "../../Common/BaseAudioProcessorEditor.h"
#include "../../Common/CustomLookAndFeel.h"
#include "../../Common/CentredLabel.h"
#include "../../Common/DbSlider.h"
#include "../../Common/WaveScopeComponent.h"
#include "../../Common/PresetBar.h"

constexpr int NUM_SLIDERS = 3;

class HayesOverdriveAudioProcessorEditor : public BaseAudioProcessorEditor
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
    
    std::unique_ptr<WaveScopeComponent<float>> scopeComponent;
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
