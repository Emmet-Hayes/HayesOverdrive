#include "HayesOverdriveAudioProcessorEditor.h"

HayesOverdriveAudioProcessorEditor::HayesOverdriveAudioProcessorEditor(HayesOverdriveAudioProcessor& p)
:   AudioProcessorEditor{ &p }
,   processor { p }
,   presetBar { p }
{
    addAllPanelComponents();
    setSize(500, 500);
    startTimerHz(60);
}

void HayesOverdriveAudioProcessorEditor::addAllPanelComponents()
{
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;

    const char* paramNames[NUM_SLIDERS] = { "input", "bias", "output" };
    const char* paramLabels[NUM_SLIDERS] = { "Input", "Bias", "Output" };
    Font font1("Lucida Console", 10.0f, Font::bold);

    for (int i = 0; i < NUM_SLIDERS; ++i)
    {
        sliderLabels[i].setText(paramLabels[i], juce::dontSendNotification);
        sliderLabels[i].setFont(font1);
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
    waveShapeBox.setLookAndFeel(&customLookAndFeel);
    addAndMakeVisible(waveShapeBox);
    
    waveShapeBoxAttachment = std::make_unique<ComboBoxAttachment>(processor.apvts, "waveshape", waveShapeBox);
    
    scopeComponent = std::make_unique<ScopeComponent<float>>(processor.audioBufferQueue);
    addAndMakeVisible(scopeComponent.get());

    presetBar.setLookAndFeel(&customLookAndFeel);
    addAndMakeVisible(presetBar);
    
    image = juce::ImageCache::getFromMemory(BinaryData::bgfile_jpg, BinaryData::bgfile_jpgSize);
}

void HayesOverdriveAudioProcessorEditor::resized()
{
    presetBar.setBounds(0, 0, 500, 20);
    sliderLabels[0].setBounds(45, 40, 80, 20);
    sliders[0]->setBounds(25, 70, 120, 120);
    sliderLabels[1].setBounds(230, 30, 80, 20);
    sliders[1]->setBounds(210, 60, 80, 80);
    sliderLabels[2].setBounds(375, 40, 80, 20);
    sliders[2]->setBounds(355, 70, 120, 120);
    waveShapeLabel.setBounds(220, 160, 80, 20);
    waveShapeBox.setBounds(210, 190, 100, 40);
    scopeComponent->setBounds(20, 250, 460, 240);
}

void HayesOverdriveAudioProcessorEditor::timerCallback()
{
    resized();
}


void HayesOverdriveAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.drawImage(image, 0, 0, 500, 500, 0, 0, 1000, 1000);
}

