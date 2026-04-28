#pragma once

#include "JuceHeader.h"
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"

#include <functional>
#include <memory>
#include <vector>

class SurgeLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider (juce::Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider&) override;

    void drawButtonBackground (juce::Graphics&, juce::Button&, const juce::Colour&,
                               bool shouldDrawButtonAsHighlighted,
                               bool shouldDrawButtonAsDown) override;

    void drawButtonText (juce::Graphics&, juce::TextButton&, bool shouldDrawButtonAsHighlighted,
                         bool shouldDrawButtonAsDown) override;

    void drawComboBox (juce::Graphics&, int width, int height, bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH,
                       juce::ComboBox&) override;

    juce::Font getComboBoxFont (juce::ComboBox&) override;
    juce::Label* createComboBoxTextBox (juce::ComboBox&) override;
    void positionComboBoxText (juce::ComboBox&, juce::Label&) override;
};

class CardComponent : public juce::Component
{
public:
    CardComponent (juce::String titleText, juce::String subtitleText);

    juce::Rectangle<int> getContentBounds() const;

    void paint (juce::Graphics&) override;
    void resized() override;

    void updateValueLabel();

private:
    juce::Label titleLabel;
    juce::Label subtitleLabel;
};

class KnobControl : public juce::Component
{
public:
    using Formatter = std::function<juce::String (double)>;

    KnobControl (juce::String titleText, juce::String hintText);

    juce::Slider& getSlider() { return slider; }
    void setFormatter (Formatter formatter);

    void resized() override;

private:
    void updateValueLabel();
    juce::Label titleLabel;
    juce::Label hintLabel;
    juce::Label valueLabel;
    juce::Slider slider;
};

class ToggleControl : public juce::Component
{
public:
    ToggleControl (juce::String titleText, juce::String hintText);

    juce::Button& getButton() { return button; }

    void resized() override;

private:
    void updateButtonText();

    juce::Label titleLabel;
    juce::Label hintLabel;
    juce::TextButton button;
};

class ChoiceControl : public juce::Component
{
public:
    ChoiceControl (juce::String titleText, juce::String hintText);

    juce::ComboBox& getComboBox() { return comboBox; }

    void resized() override;

private:
    juce::Label titleLabel;
    juce::Label hintLabel;
    juce::ComboBox comboBox;
};

class CustomAudioEditor : public juce::AudioProcessorEditor
{
public:
    CustomAudioEditor (RNBO::JuceAudioProcessor* p, RNBO::CoreObject& rnboObject);
    ~CustomAudioEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::RangedAudioParameter& getParameter (const juce::String& parameterID) const;

    static juce::String formatPercent (double value);
    static juce::String formatFrequency (double value);
    static juce::String formatDecimal (double value);

    RNBO::JuceAudioProcessor& audioProcessor;
    SurgeLookAndFeel lookAndFeel;

    juce::Label titleLabel;
    juce::Label subtitleLabel;
    juce::Label footerLabel;

    CardComponent motionCard;
    CardComponent toneCard;
    CardComponent bandsCard;
    CardComponent behaviorCard;

    KnobControl amountKnob;
    KnobControl speedKnob;
    KnobControl chopKnob;
    KnobControl sensitivityKnob;
    KnobControl liftKnob;

    KnobControl lowKnob;
    KnobControl bodyKnob;
    KnobControl airKnob;

    KnobControl lowSplitKnob;
    KnobControl highSplitKnob;
    KnobControl adaptiveAlphaKnob;

    ToggleControl bandAwareToggle;
    ToggleControl adaptiveModeToggle;
    ChoiceControl syncModeChoice;

    std::vector<std::unique_ptr<juce::SliderParameterAttachment>> sliderAttachments;
    std::vector<std::unique_ptr<juce::ButtonParameterAttachment>> buttonAttachments;
    std::vector<std::unique_ptr<juce::ComboBoxParameterAttachment>> comboAttachments;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioEditor)
};
