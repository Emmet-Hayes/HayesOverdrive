#pragma once
#include <JuceHeader.h>
#include <unordered_map>

class CustomLookAndFeel : public LookAndFeel_V4
{
public:
	CustomLookAndFeel();
	void drawRotarySlider(Graphics&, int, int, int, int, float, const float,
		const float, Slider&) override;
	void drawComboBox(Graphics&, int, int, bool, int, int, int, int, ComboBox&) override;
	Font getComboBoxFont(ComboBox&) override;
	Font getPopupMenuFont() override;
	void drawPopupMenuBackground(Graphics&, int, int) override;
	inline void setScale(const float s) { scale = s; }

private:
	Font getCommonMenuFont(float);

	float scale = 1.0f;
	float rotaryOutlineBrightness = 1.0f;

};
