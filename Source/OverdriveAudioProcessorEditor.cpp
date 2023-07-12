#include "OverdriveAudioProcessorEditor.h"

OverdriveAudioProcessorEditor::OverdriveAudioProcessorEditor(OverdriveAudioProcessor& p)
:   AudioProcessorEditor (&p)
,   processor (p)
{
    addAllPanelComponents();
    setSize(400, 250);
}

void OverdriveAudioProcessorEditor::addAllPanelComponents()
{
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    const char* paramNames[NUM_SLIDERS] = { "input", "bias", "output" };
    const char* paramLabels[NUM_SLIDERS] = { "Input", "Bias", "Output" };

    for (int i = 0; i < NUM_SLIDERS; ++i)
    {
        sliderLabels[i].setText(paramLabels[i], juce::dontSendNotification);
        addAndMakeVisible(sliderLabels[i]);
        if (i == 0 || i == 2)
            sliders[i] = std::make_unique<DbSlider>();
        else
            sliders[i] = std::make_unique<juce::Slider>();

        sliders[i]->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
        sliders[i]->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
        sliders[i]->setLookAndFeel(&customLookAndFeel);
        addAndMakeVisible(sliders[i].get());
        sliderAttachments[i] = std::make_unique<Attachment>(processor.apvts, paramNames[i], *sliders[i]);
    }

    waveShapeLabel.setText("Wave Shape", juce::dontSendNotification);
    addAndMakeVisible(waveShapeLabel);
    waveShapeBox.addItemList(juce::StringArray{ "Tanh", "Sin", "Soft", "Hard", "Arctan", "Sigmoid", "Hard Tanh", "Absolute Value" }, 1);
    waveShapeBox.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(waveShapeBox);
    
    waveShapeBoxAttachment = std::make_unique<ComboBoxAttachment>(processor.apvts, "waveshape", waveShapeBox);
    
    image = juce::ImageCache::getFromMemory(BinaryData::bgfile_jpg, BinaryData::bgfile_jpgSize);
}

void OverdriveAudioProcessorEditor::resized()
{
    sliderLabels[0].setBounds(45, 20, 80, 20);
    sliders[0]->setBounds(15, 50, 120, 120);
    sliderLabels[1].setBounds(182, 20, 80, 20);
    sliders[1]->setBounds(158, 50, 80, 80);
    sliderLabels[2].setBounds(295, 20, 80, 20);
    sliders[2]->setBounds(271, 50, 120, 120);
    waveShapeLabel.setBounds(168, 150, 80, 20);
    waveShapeBox.setBounds(158, 180, 100, 40);
}


void OverdriveAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.drawImage(image, 0, 0, 400, 250, 0, 0, 800, 500);
}

