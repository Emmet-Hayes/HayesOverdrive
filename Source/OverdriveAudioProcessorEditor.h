#pragma once
#include "OverdriveAudioProcessor.h"
#include "CustomLookAndFeel.h"
#include "CentredLabel.h"
#include "DbSlider.h"

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

    DbSlider inputSlider;
    DbSlider outputSlider;
    
    CentredLabel inputLabel;
    CentredLabel outputLabel;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<Attachment> inputAttachment;
    std::unique_ptr<Attachment> outputAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OverdriveAudioProcessorEditor)
};
