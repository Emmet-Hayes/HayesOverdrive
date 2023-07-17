#pragma once
#include <JuceHeader.h>
#include "HayesOverdriveAudioProcessor.h"

class PresetBar;

class PresetComboBox : public juce::ComboBox
{
public:
    PresetComboBox(HayesOverdriveAudioProcessor& p, PresetBar* bar);
    void mouseDown(const juce::MouseEvent& event) override;
    void savePreset();
    void loadPreset();
    void deletePreset();

    HayesOverdriveAudioProcessor& processor;
    PresetBar* presetBar;
    juce::PopupMenu saveLoadMenu;
};
