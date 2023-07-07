#include "OverdriveAudioProcessorEditor.h"

OverdriveAudioProcessorEditor::OverdriveAudioProcessorEditor(OverdriveAudioProcessor& p)
:   AudioProcessorEditor (&p)
,   processor (p)
{
    setSize (250, 200);
    addAllPanelComponents();
}


OverdriveAudioProcessorEditor::~OverdriveAudioProcessorEditor()
{
    inputAttachment = nullptr;
    outputAttachment = nullptr;
}

void OverdriveAudioProcessorEditor::addAllPanelComponents()
{
    inputLabel.setText("Input", juce::dontSendNotification);
    addAndMakeVisible(inputLabel);
    inputSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    inputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    inputSlider.setLookAndFeel(&customLookAndFeel);
    addAndMakeVisible(inputSlider);
    inputAttachment = std::make_unique<Attachment>(processor.apvts, "input", inputSlider);

    outputLabel.setText("Output", juce::dontSendNotification);
    addAndMakeVisible(outputLabel);
    outputSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    outputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    outputSlider.setLookAndFeel(&customLookAndFeel);
    addAndMakeVisible (outputSlider);
    outputAttachment = std::make_unique<Attachment>(processor.apvts, "output", outputSlider);
    
    image = juce::ImageCache::getFromMemory(BinaryData::bgfile_jpg, BinaryData::bgfile_jpgSize);
}

void OverdriveAudioProcessorEditor::resized()
{
    inputLabel.setBounds (37, 20, 80, 40);
    inputSlider.setBounds (10, 60, 100, 100);
    outputLabel.setBounds (150, 20, 80, 40);
    outputSlider.setBounds (123, 60, 100, 100);
}


void OverdriveAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.drawImage(image, 0, 0, 250, 200, 0, 0, 500, 400);
}

