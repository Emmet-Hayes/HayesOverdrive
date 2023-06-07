/*
  ==============================================================================

    OverdriveAudioProcessorEditor.h
    Created: 7 Jun 2023 2:58:14pm
    Author:  emmet

  ==============================================================================
*/

#pragma once
#include "OverdriveAudioProcessor.h"
#include "CustomLookAndFeel.h"

class OverdriveAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    OverdriveAudioProcessorEditor(OverdriveAudioProcessor& p);
    ~OverdriveAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void addAllPanelComponents();

    OverdriveAudioProcessor& processor;
    
    CustomLookAndFeel customLookAndFeel;
    juce::Image image;

    juce::Slider inputSlider;
    juce::Slider outputSlider;
    
    juce::Label inputLabel;
    juce::Label outputLabel;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<Attachment> inputAttachment;
    std::unique_ptr<Attachment> outputAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OverdriveAudioProcessorEditor)
};
