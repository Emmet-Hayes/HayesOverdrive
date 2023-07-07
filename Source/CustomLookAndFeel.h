#pragma once

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:

void drawComboBox (juce::Graphics& g, int width, int height, bool /*isButtonDown*/,
                   int buttonX, int buttonY, int buttonW, int buttonH,
                   juce::ComboBox& box) override
{
    auto cornerSize = box.findParentComponentOfClass<juce::ChoicePropertyComponent>() != nullptr ? 0.0f : 5.0f;
    juce::Rectangle<int> boxBounds(0, 0, width, height);

    g.setColour(juce::Colours::darkgrey);
    g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

    g.setColour(juce::Colours::silver);
    g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), cornerSize, 1.0f);

    juce::Path path;
    path.startNewSubPath(buttonX + buttonW * 0.5f, buttonY + buttonH * 0.3f);
    path.lineTo(buttonX + buttonW * 0.1f, buttonY + buttonH * 0.7f);
    path.lineTo(buttonX + buttonW * 0.9f, buttonY + buttonH * 0.7f);
    path.closeSubPath();

    g.setColour(box.findColour(juce::ComboBox::arrowColourId).withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
    g.fillPath(path);
}

};
