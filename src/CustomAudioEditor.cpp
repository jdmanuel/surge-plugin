#include "CustomAudioEditor.h"

namespace
{
const auto backgroundTop = juce::Colour (0xff0e151c);
const auto backgroundBottom = juce::Colour (0xff121c26);
const auto panelTop = juce::Colour (0xff1b2733);
const auto panelBottom = juce::Colour (0xff141d27);
const auto panelOutline = juce::Colour (0x3dffffff);
const auto textPrimary = juce::Colour (0xffeef5fb);
const auto textSecondary = juce::Colour (0xffc0cfdd);
const auto textMuted = juce::Colour (0xff7d8d9e);
const auto accent = juce::Colour (0xfff59e0b);
const auto accentSoft = juce::Colour (0xfffb7185);
const auto coolGlow = juce::Colour (0xff38bdf8);
const auto knobFillTop = juce::Colour (0xff253444);
const auto knobFillBottom = juce::Colour (0xff1a2430);
const auto knobTrack = juce::Colour (0x25ffffff);

void styleLabel (juce::Label& label, float size, bool bold, juce::Colour colour)
{
    label.setFont (juce::Font (juce::FontOptions (size, bold ? juce::Font::bold : juce::Font::plain)));
    label.setColour (juce::Label::textColourId, colour);
    label.setInterceptsMouseClicks (false, false);
}

void layoutGrid (juce::Rectangle<int> area,
                 std::initializer_list<juce::Component*> components,
                 int columns,
                 int rowGap = 12,
                 int columnGap = 12)
{
    const auto count = static_cast<int> (components.size());

    if (count == 0 || columns <= 0)
        return;

    const int rows = juce::jmax (1, (count + columns - 1) / columns);
    const int cellWidth = (area.getWidth() - columnGap * (columns - 1)) / columns;
    const int cellHeight = (area.getHeight() - rowGap * (rows - 1)) / rows;

    int index = 0;
    for (auto* component : components)
    {
        const int row = index / columns;
        const int column = index % columns;

        component->setBounds (area.getX() + column * (cellWidth + columnGap),
                              area.getY() + row * (cellHeight + rowGap),
                              cellWidth,
                              cellHeight);
        ++index;
    }
}
}

void SurgeLookAndFeel::drawRotarySlider (juce::Graphics& g,
                                         int x,
                                         int y,
                                         int width,
                                         int height,
                                         float sliderPosProportional,
                                         float rotaryStartAngle,
                                         float rotaryEndAngle,
                                         juce::Slider&)
{
    auto bounds = juce::Rectangle<float> ((float) x, (float) y, (float) width, (float) height).reduced (10.0f, 8.0f);
    const auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) * 0.5f;
    const auto centre = bounds.getCentre();
    const auto knobRadius = radius - 8.0f;
    auto knobBounds = juce::Rectangle<float> (centre.x - knobRadius,
                                              centre.y - knobRadius,
                                              knobRadius * 2.0f,
                                              knobRadius * 2.0f);

    g.setColour (juce::Colours::black.withAlpha (0.18f));
    g.fillEllipse (knobBounds.translated (0.0f, 5.0f));

    juce::ColourGradient knobGradient (knobFillTop, knobBounds.getTopLeft(), knobFillBottom, knobBounds.getBottomRight(), false);
    g.setGradientFill (knobGradient);
    g.fillEllipse (knobBounds);

    g.setColour (juce::Colours::white.withAlpha (0.07f));
    g.drawEllipse (knobBounds.reduced (0.75f), 1.2f);

    const auto trackRadius = knobRadius - 7.0f;
    const auto trackThickness = 9.0f;
    const auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    juce::Path backgroundArc;
    backgroundArc.addCentredArc (centre.x, centre.y,
                                 trackRadius, trackRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);

    g.setColour (knobTrack);
    g.strokePath (backgroundArc, juce::PathStrokeType (trackThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    juce::Path valueArc;
    valueArc.addCentredArc (centre.x, centre.y,
                            trackRadius, trackRadius,
                            0.0f,
                            rotaryStartAngle,
                            toAngle,
                            true);

    juce::ColourGradient valueGradient (accent.brighter (0.15f), centre.x, (float) y,
                                        accentSoft, centre.x, (float) (y + height), false);
    g.setGradientFill (valueGradient);
    g.strokePath (valueArc, juce::PathStrokeType (trackThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    juce::Path pointer;
    pointer.addRoundedRectangle (-1.8f, -trackRadius + 7.0f, 3.6f, trackRadius * 0.55f, 1.8f);

    g.setColour (juce::Colour (0xfffff7ed));
    g.fillPath (pointer, juce::AffineTransform::rotation (toAngle).translated (centre.x, centre.y));

    g.setColour (juce::Colours::white.withAlpha (0.12f));
    g.fillEllipse (juce::Rectangle<float> (centre.x - 11.0f, centre.y - 11.0f, 22.0f, 22.0f));

    g.setColour (juce::Colour (0xff10161d));
    g.fillEllipse (juce::Rectangle<float> (centre.x - 8.5f, centre.y - 8.5f, 17.0f, 17.0f));
}

void SurgeLookAndFeel::drawButtonBackground (juce::Graphics& g,
                                             juce::Button& button,
                                             const juce::Colour&,
                                             bool shouldDrawButtonAsHighlighted,
                                             bool shouldDrawButtonAsDown)
{
    auto bounds = button.getLocalBounds().toFloat().reduced (1.0f);
    auto fill = button.getToggleState() ? accent : juce::Colour (0xff243240);

    if (shouldDrawButtonAsHighlighted)
        fill = fill.brighter (0.08f);

    if (shouldDrawButtonAsDown)
        fill = fill.darker (0.12f);

    juce::ColourGradient gradient (fill.brighter (0.12f), bounds.getTopLeft(), fill.darker (0.16f), bounds.getBottomRight(), false);

    g.setColour (juce::Colours::black.withAlpha (0.16f));
    g.fillRoundedRectangle (bounds.translated (0.0f, 3.0f), bounds.getHeight() * 0.5f);

    g.setGradientFill (gradient);
    g.fillRoundedRectangle (bounds, bounds.getHeight() * 0.5f);

    g.setColour (button.getToggleState() ? juce::Colours::white.withAlpha (0.18f) : panelOutline);
    g.drawRoundedRectangle (bounds, bounds.getHeight() * 0.5f, 1.0f);
}

void SurgeLookAndFeel::drawButtonText (juce::Graphics& g,
                                       juce::TextButton& button,
                                       bool,
                                       bool)
{
    g.setColour (textPrimary);
    g.setFont (juce::Font (juce::FontOptions (14.0f, juce::Font::bold)));
    g.drawFittedText (button.getButtonText(), button.getLocalBounds().reduced (12, 0), juce::Justification::centred, 1);
}

void SurgeLookAndFeel::drawComboBox (juce::Graphics& g,
                                     int width,
                                     int height,
                                     bool isButtonDown,
                                     int,
                                     int,
                                     int,
                                     int,
                                     juce::ComboBox&)
{
    auto bounds = juce::Rectangle<float> (0.0f, 0.0f, (float) width, (float) height).reduced (1.0f);
    auto fill = juce::Colour (0xff243240);

    if (isButtonDown)
        fill = fill.brighter (0.06f);

    juce::ColourGradient gradient (fill.brighter (0.1f), bounds.getTopLeft(), fill.darker (0.16f), bounds.getBottomRight(), false);

    g.setColour (juce::Colours::black.withAlpha (0.16f));
    g.fillRoundedRectangle (bounds.translated (0.0f, 3.0f), 12.0f);

    g.setGradientFill (gradient);
    g.fillRoundedRectangle (bounds, 12.0f);

    g.setColour (panelOutline);
    g.drawRoundedRectangle (bounds, 12.0f, 1.0f);

    juce::Path arrow;
    const float arrowX = bounds.getRight() - 18.0f;
    const float arrowY = bounds.getCentreY();
    arrow.startNewSubPath (arrowX - 5.0f, arrowY - 2.5f);
    arrow.lineTo (arrowX, arrowY + 3.0f);
    arrow.lineTo (arrowX + 5.0f, arrowY - 2.5f);

    g.setColour (textSecondary);
    g.strokePath (arrow, juce::PathStrokeType (1.7f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
}

juce::Font SurgeLookAndFeel::getComboBoxFont (juce::ComboBox&)
{
    return juce::Font (juce::FontOptions (14.0f, juce::Font::bold));
}

juce::Label* SurgeLookAndFeel::createComboBoxTextBox (juce::ComboBox&)
{
    auto* label = new juce::Label();
    label->setFont (juce::Font (juce::FontOptions (14.0f, juce::Font::bold)));
    label->setColour (juce::Label::textColourId, textPrimary);
    label->setColour (juce::Label::backgroundColourId, juce::Colours::transparentBlack);
    return label;
}

void SurgeLookAndFeel::positionComboBoxText (juce::ComboBox& box, juce::Label& label)
{
    label.setBounds (2, 1, box.getWidth() - 28, box.getHeight() - 2);
    label.setFont (getComboBoxFont (box));
    label.setJustificationType (juce::Justification::centredLeft);
}

CardComponent::CardComponent (juce::String titleText, juce::String subtitleText)
{
    titleLabel.setText (titleText, juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centredLeft);
    styleLabel (titleLabel, 17.0f, true, textPrimary);
    addAndMakeVisible (titleLabel);

    subtitleLabel.setText (subtitleText, juce::dontSendNotification);
    subtitleLabel.setJustificationType (juce::Justification::centredLeft);
    styleLabel (subtitleLabel, 12.5f, false, textMuted);
    addAndMakeVisible (subtitleLabel);
}

juce::Rectangle<int> CardComponent::getContentBounds() const
{
    auto area = getLocalBounds().reduced (16);
    area.removeFromTop (46);
    return area;
}

void CardComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced (1.5f);

    g.setColour (juce::Colours::black.withAlpha (0.20f));
    g.fillRoundedRectangle (bounds.translated (0.0f, 7.0f), 22.0f);

    juce::ColourGradient gradient (panelTop, bounds.getTopLeft(), panelBottom, bounds.getBottomRight(), false);
    g.setGradientFill (gradient);
    g.fillRoundedRectangle (bounds, 22.0f);

    g.setColour (panelOutline);
    g.drawRoundedRectangle (bounds, 22.0f, 1.0f);

    g.setColour (accent.withAlpha (0.18f));
    g.fillRoundedRectangle (juce::Rectangle<float> (bounds.getX() + 16.0f, bounds.getY() + 14.0f, 46.0f, 3.0f), 1.5f);
}

void CardComponent::resized()
{
    auto area = getLocalBounds().reduced (16);
    titleLabel.setBounds (area.removeFromTop (22));
    subtitleLabel.setBounds (area.removeFromTop (18));
}

KnobControl::KnobControl (juce::String titleText, juce::String hintText)
{
    titleLabel.setText (titleText, juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centred);
    styleLabel (titleLabel, 13.0f, true, textSecondary);
    addAndMakeVisible (titleLabel);

    hintLabel.setText (hintText, juce::dontSendNotification);
    hintLabel.setJustificationType (juce::Justification::centredTop);
    styleLabel (hintLabel, 11.0f, false, textMuted);
    addAndMakeVisible (hintLabel);

    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 72, 20);
    slider.setRotaryParameters (juce::MathConstants<float>::pi * 1.2f,
                                juce::MathConstants<float>::pi * 2.8f,
                                true);
    slider.setScrollWheelEnabled (false);
    slider.setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    slider.setColour (juce::Slider::textBoxBackgroundColourId, juce::Colour (0x20ffffff));
    slider.setColour (juce::Slider::textBoxTextColourId, textPrimary);
    slider.setColour (juce::Slider::textBoxHighlightColourId, juce::Colours::transparentBlack);
    addAndMakeVisible (slider);
}

void KnobControl::setFormatter (Formatter formatter)
{
    slider.textFromValueFunction = std::move (formatter);
}

void KnobControl::resized()
{
    auto area = getLocalBounds().reduced (4);
    titleLabel.setBounds (area.removeFromTop (18));
    hintLabel.setBounds (area.removeFromBottom (16));
    slider.setBounds (area);
}

ToggleControl::ToggleControl (juce::String titleText, juce::String hintText)
{
    titleLabel.setText (titleText, juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centredLeft);
    styleLabel (titleLabel, 13.0f, true, textSecondary);
    addAndMakeVisible (titleLabel);

    hintLabel.setText (hintText, juce::dontSendNotification);
    hintLabel.setJustificationType (juce::Justification::centredLeft);
    styleLabel (hintLabel, 11.0f, false, textMuted);
    addAndMakeVisible (hintLabel);

    button.setClickingTogglesState (true);
    button.onStateChange = [this] { updateButtonText(); };
    addAndMakeVisible (button);
    updateButtonText();
}

void ToggleControl::resized()
{
    auto area = getLocalBounds().reduced (6);
    titleLabel.setBounds (area.removeFromTop (18));
    hintLabel.setBounds (area.removeFromBottom (16));
    button.setBounds (area.removeFromTop (34));
}

void ToggleControl::updateButtonText()
{
    button.setButtonText (button.getToggleState() ? "On" : "Off");
}

ChoiceControl::ChoiceControl (juce::String titleText, juce::String hintText)
{
    titleLabel.setText (titleText, juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centredLeft);
    styleLabel (titleLabel, 13.0f, true, textSecondary);
    addAndMakeVisible (titleLabel);

    hintLabel.setText (hintText, juce::dontSendNotification);
    hintLabel.setJustificationType (juce::Justification::centredLeft);
    styleLabel (hintLabel, 11.0f, false, textMuted);
    addAndMakeVisible (hintLabel);

    comboBox.setColour (juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    comboBox.setColour (juce::ComboBox::backgroundColourId, juce::Colours::transparentBlack);
    comboBox.setColour (juce::ComboBox::textColourId, textPrimary);
    addAndMakeVisible (comboBox);
}

void ChoiceControl::resized()
{
    auto area = getLocalBounds().reduced (6);
    titleLabel.setBounds (area.removeFromTop (18));
    hintLabel.setBounds (area.removeFromBottom (16));
    comboBox.setBounds (area.removeFromTop (34));
}

CustomAudioEditor::CustomAudioEditor (RNBO::JuceAudioProcessor* p, RNBO::CoreObject& rnboObject)
    : juce::AudioProcessorEditor (p)
    , audioProcessor (*p)
    , motionCard ("Motion", "Dial in depth, pace, and overall feel.")
    , toneCard ("Tone", "Balance the low end, body, and top sheen.")
    , bandsCard ("Bands", "Shape how motion behaves across the spectrum.")
    , behaviorCard ("Behavior", "Control sync and adaptive response.")
    , amountKnob ("Amount", "overall movement depth")
    , speedKnob ("Speed", "rate of the surge")
    , chopKnob ("Chop", "edginess of the motion")
    , sensitivityKnob ("Sensitivity", "how eagerly it reacts")
    , liftKnob ("Lift", "how much it opens up")
    , lowKnob ("Low", "weight and foundation")
    , bodyKnob ("Body", "midrange density")
    , airKnob ("Air", "top-end openness")
    , lowSplitKnob ("Low Split", "where the low band ends")
    , highSplitKnob ("High Split", "where the high band starts")
    , adaptiveAlphaKnob ("Adaptive Alpha", "smoothness of adaptation")
    , bandAwareToggle ("Band Aware", "let each band move on its own")
    , adaptiveModeToggle ("Adaptive Mode", "follow program material more actively")
    , syncModeChoice ("Sync Mode", "free run or host-synced motion")
{
    juce::ignoreUnused (rnboObject);

    setLookAndFeel (&lookAndFeel);
    setOpaque (true);

    titleLabel.setText ("Surge", juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centredLeft);
    styleLabel (titleLabel, 32.0f, true, textPrimary);

    subtitleLabel.setText ("A focused editor for motion, crossover shaping, and tonal balance.", juce::dontSendNotification);
    subtitleLabel.setJustificationType (juce::Justification::centredLeft);
    styleLabel (subtitleLabel, 14.0f, false, textSecondary);

    footerLabel.setText ("Tip: Start with Amount, Speed, and Body. Use the split points with Band Aware to make the motion react differently across the spectrum.",
                         juce::dontSendNotification);
    footerLabel.setJustificationType (juce::Justification::centredLeft);
    styleLabel (footerLabel, 12.0f, false, textMuted);

    for (auto* component : {
             static_cast<juce::Component*> (&titleLabel),
             static_cast<juce::Component*> (&subtitleLabel),
             static_cast<juce::Component*> (&footerLabel),
             static_cast<juce::Component*> (&motionCard),
             static_cast<juce::Component*> (&toneCard),
             static_cast<juce::Component*> (&bandsCard),
             static_cast<juce::Component*> (&behaviorCard),
             static_cast<juce::Component*> (&amountKnob),
             static_cast<juce::Component*> (&speedKnob),
             static_cast<juce::Component*> (&chopKnob),
             static_cast<juce::Component*> (&sensitivityKnob),
             static_cast<juce::Component*> (&liftKnob),
             static_cast<juce::Component*> (&lowKnob),
             static_cast<juce::Component*> (&bodyKnob),
             static_cast<juce::Component*> (&airKnob),
             static_cast<juce::Component*> (&lowSplitKnob),
             static_cast<juce::Component*> (&highSplitKnob),
             static_cast<juce::Component*> (&adaptiveAlphaKnob),
             static_cast<juce::Component*> (&bandAwareToggle),
             static_cast<juce::Component*> (&adaptiveModeToggle),
             static_cast<juce::Component*> (&syncModeChoice)
         })
    {
        addAndMakeVisible (*component);
    }

    sliderAttachments.reserve (11);
    buttonAttachments.reserve (2);
    comboAttachments.reserve (1);

    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("amount"), amountKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("speed"), speedKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("chop"), chopKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("sensitivity"), sensitivityKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("lift"), liftKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("low"), lowKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("body"), bodyKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("air"), airKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("low_split"), lowSplitKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("high_split"), highSplitKnob.getSlider(), nullptr));
    sliderAttachments.push_back (std::make_unique<juce::SliderParameterAttachment> (getParameter ("adaptive_alpha"), adaptiveAlphaKnob.getSlider(), nullptr));

    buttonAttachments.push_back (std::make_unique<juce::ButtonParameterAttachment> (getParameter ("band_surge"), bandAwareToggle.getButton(), nullptr));
    buttonAttachments.push_back (std::make_unique<juce::ButtonParameterAttachment> (getParameter ("adaptive_mode"), adaptiveModeToggle.getButton(), nullptr));

    syncModeChoice.getComboBox().addItemList (juce::StringArray { "Free", "Synced" }, 1);
    comboAttachments.push_back (std::make_unique<juce::ComboBoxParameterAttachment> (getParameter ("sync_mode"), syncModeChoice.getComboBox(), nullptr));

    amountKnob.setFormatter (formatPercent);
    speedKnob.setFormatter (formatPercent);
    chopKnob.setFormatter (formatPercent);
    sensitivityKnob.setFormatter (formatPercent);
    liftKnob.setFormatter (formatPercent);
    lowKnob.setFormatter (formatPercent);
    bodyKnob.setFormatter (formatPercent);
    airKnob.setFormatter (formatPercent);
    adaptiveAlphaKnob.setFormatter (formatDecimal);
    lowSplitKnob.setFormatter (formatFrequency);
    highSplitKnob.setFormatter (formatFrequency);

    lowSplitKnob.getSlider().setSkewFactorFromMidPoint (400.0);
    highSplitKnob.getSlider().setSkewFactorFromMidPoint (1200.0);

    setSize (980, 660);
}

CustomAudioEditor::~CustomAudioEditor()
{
    setLookAndFeel (nullptr);
}

void CustomAudioEditor::paint (juce::Graphics& g)
{
    juce::ColourGradient background (backgroundTop, 0.0f, 0.0f,
                                     backgroundBottom, 0.0f, (float) getHeight(), false);
    background.addColour (0.5, juce::Colour (0xff17222d));
    g.setGradientFill (background);
    g.fillAll();

    g.setColour (accent.withAlpha (0.10f));
    g.fillEllipse (-110.0f, -70.0f, 330.0f, 220.0f);

    g.setColour (coolGlow.withAlpha (0.08f));
    g.fillEllipse ((float) getWidth() - 260.0f, 36.0f, 300.0f, 220.0f);
}

void CustomAudioEditor::resized()
{
    auto area = getLocalBounds().reduced (22);
    auto header = area.removeFromTop (72);

    titleLabel.setBounds (header.removeFromTop (36));
    subtitleLabel.setBounds (header.removeFromTop (24));

    area.removeFromTop (8);
    footerLabel.setBounds (area.removeFromBottom (22));
    area.removeFromBottom (6);

    const int gap = 16;
    const auto contentWidth = area.getWidth();
    const int leftColumnWidth = juce::roundToInt ((contentWidth - gap) * 0.58f);

    auto topRow = area.removeFromTop ((area.getHeight() - gap) / 2);
    auto bottomRow = area;

    motionCard.setBounds (topRow.removeFromLeft (leftColumnWidth));
    topRow.removeFromLeft (gap);
    behaviorCard.setBounds (topRow);

    toneCard.setBounds (bottomRow.removeFromLeft (leftColumnWidth));
    bottomRow.removeFromLeft (gap);
    bandsCard.setBounds (bottomRow);

    layoutGrid (motionCard.getContentBounds(),
                { &amountKnob, &speedKnob, &chopKnob, &sensitivityKnob, &liftKnob },
                5);

    layoutGrid (toneCard.getContentBounds(),
                { &lowKnob, &bodyKnob, &airKnob },
                3);

    auto behaviorBounds = behaviorCard.getContentBounds();
    auto behaviorTop = behaviorBounds.removeFromTop ((behaviorBounds.getHeight() - 12) / 2);
    behaviorBounds.removeFromTop (12);

    layoutGrid (behaviorTop,
                { &adaptiveModeToggle, &syncModeChoice },
                2);

    layoutGrid (behaviorBounds,
                { &adaptiveAlphaKnob },
                1);

    layoutGrid (bandsCard.getContentBounds(),
                { &lowSplitKnob, &highSplitKnob, &bandAwareToggle },
                3);
}

juce::RangedAudioParameter& CustomAudioEditor::getParameter (const juce::String& parameterID) const
{
    for (auto* parameter : audioProcessor.getParameters())
    {
        if (auto* ranged = dynamic_cast<juce::RangedAudioParameter*> (parameter))
        {
            if (ranged->getParameterID() == parameterID)
                return *ranged;
        }
    }

    jassertfalse;
    return *dynamic_cast<juce::RangedAudioParameter*> (audioProcessor.getParameters()[0]);
}

juce::String CustomAudioEditor::formatPercent (double value)
{
    return juce::String (juce::roundToInt (value * 100.0)) + "%";
}

juce::String CustomAudioEditor::formatFrequency (double value)
{
    if (value >= 1000.0)
    {
        const auto kiloHertz = value / 1000.0;
        return juce::String (kiloHertz, kiloHertz >= 10.0 ? 1 : 2) + " kHz";
    }

    return juce::String (juce::roundToInt (value)) + " Hz";
}

juce::String CustomAudioEditor::formatDecimal (double value)
{
    return juce::String (value, 2);
}
