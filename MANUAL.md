# Surge User Guide

Surge is a band-aware tremolo and motion effect.

Instead of applying one fixed tremolo shape to the whole signal, it listens to the incoming audio, turns that movement into control signals, and lets different parts of the spectrum surge differently. The result can feel anything from gentle breathing to choppy, animated rhythmic motion.

## The Big Idea

Surge works in three layers:

- `Motion` sets how strong, fast, sharp, and reactive the movement feels.
- `Tone` sets how strongly the low, mid, and high parts of the signal drive that movement.
- `Bands` decides whether the whole spectrum moves together, or whether lows, mids, and highs can move differently.

If you only remember one thing, remember this:

- `Amount`, `Speed`, `Chop`, `Sensitivity`, and `Lift` shape the character of the motion.
- `Low`, `Body`, and `Air` decide which parts of the spectrum push that motion harder.
- `Band Mode`, `Low Split`, and `High Split` decide whether that motion is shared or split across frequency regions.

## Quick Start

1. Start with `Band Mode` set to `1 Band` if you want a simple whole-signal tremolo feel.
2. Move to `2 Bands` or `3 Bands` if you want lows and highs to move differently.
3. Set `Amount` first.
4. Set `Speed` and `Chop` next to decide whether the motion feels smooth or sharp.
5. Raise `Sensitivity` if you want the effect to react more strongly to the input.
6. Use `Low`, `Body`, and `Air` to decide which frequency areas surge harder.
7. Turn on `Adaptive Mode` if you want the split behavior to follow the incoming material more dynamically.

## Controls

### Motion

### Amount

Controls overall modulation depth.

- Lower values feel subtle and mix-friendly.
- Higher values create deeper volume movement and more obvious pumping.

Use this as your main "how much effect" control.

### Speed

Controls the pace of the surge.

- In `Free` mode, it behaves like a faster or slower modulation rate.
- In `Synced` mode, it shifts toward slower or faster tempo-related feels.

Lower settings feel slower and more spacious. Higher settings feel more urgent and animated.

### Chop

Controls how rounded or abrupt the movement is.

- Lower values feel smoother, softer, and more wave-like.
- Higher values feel tighter, sharper, and more gated.

If you want a breathing effect, keep this lower. If you want stutter, pulse, or edge, push it up.

### Sensitivity

Controls how strongly the motion responds to changes in the input.

- Lower values keep the movement steadier and less jumpy.
- Higher values make the effect react more aggressively to transients, accents, and changes in spectral balance.

If Surge feels too nervous, lower this first.

### Lift

Controls how much the motion "opens up" instead of clamping down.

- Lower values feel more like classic ducking or tremolo dips.
- Higher values keep more signal present between dips and make the motion feel more lifted, airy, and blooming.

If the effect feels too pinched or too hard-muted, raise `Lift`.

### Tone

These controls do not act like a normal EQ. They do not simply boost or cut audio bands.

They scale how strongly each spectral region drives the motion engine. More drive means that region tends to create faster, deeper, and tighter modulation behavior. Less drive makes that region calmer.

`50%` is the neutral center for these controls.

### Low

Controls how strongly bass and low-mid content drive the motion.

- Raise it if you want kicks, bass, and warmth to make the effect swell harder.
- Lower it if the low end is moving too much or feels unstable.

### Body

Controls how strongly the midrange drives the motion.

- Raise it for more vocal, guitar, synth, and snare responsiveness.
- Lower it if the middle of the sound feels too busy or too animated.

### Air

Controls how strongly upper mids and highs drive the motion.

- Raise it for more shimmer, bite, and top-end animation.
- Lower it if cymbals, fizz, or brightness are making the effect too twitchy.

### Bands

### Band Mode

This chooses how many reactive regions Surge uses.

### 1 Band

The whole spectrum shares one motion profile.

This is the simplest mode and feels closest to a classic tremolo, but still with Surge's reactive behavior.

### 2 Bands

The lows get their own motion, and everything above the `Low Split` shares another motion.

This is often the best balance between clarity and animation.

### 3 Bands

Lows, mids, and highs all get their own motion profile.

This is the most expressive mode and the easiest place to hear `Low`, `Body`, and `Air` diverge in a dramatic way.

### Low Split

Sets where the low band ends.

- Lower values create a smaller low band.
- Higher values create a wider low band.

In `2 Bands`, this is the main crossover.

In `3 Bands`, this sets the boundary between low and mid.

### High Split

Sets where the high band starts.

- Lower values make the high band begin earlier.
- Higher values keep more material in the mid band before handing off to the highs.

This is mainly useful in `3 Bands`.

### Important note about Band Mode

The `Band Mode` switch is a shortcut that sets starting split points:

- `1 Band` sets `Low Split = 0` and `High Split = 0`
- `2 Bands` sets `Low Split = 800 Hz` and `High Split = 0`
- `3 Bands` sets `Low Split = 800 Hz` and `High Split = 2000 Hz`

After that, you are free to move the split knobs anywhere you like.

### Behavior

### Adaptive Mode

When `Adaptive Mode` is off, the split points stay fixed where you put them.

When `Adaptive Mode` is on, Surge analyzes the incoming material and shifts its internal split behavior so the motion tracks the spectral center of the sound more intelligently.

Use this when the source changes a lot over time and you want the effect to feel more alive and program-aware.

### Adaptive Alpha

Controls how quickly Adaptive Mode responds.

- Lower values are smoother and slower.
- Higher values follow changes more quickly and can feel more lively or more restless.

If Adaptive Mode feels too jumpy, lower `Adaptive Alpha`.

### Sync Mode

Controls whether the movement is free-running or host-synced.

- `Free` gives you an unconstrained modulation feel.
- `Synced` ties the motion feel to your DAW's tempo and transport.

Use `Free` for organic motion. Use `Synced` when you want the movement to lock into a groove.

## How The Controls Work Together

Here is the easiest way to think about the interactions:

- `Amount` changes how deep the motion goes.
- `Speed` changes how fast it cycles.
- `Chop` changes how hard the edges feel.
- `Sensitivity` changes how much the input can push the movement around.
- `Lift` changes how open or clamped the movement feels.
- `Low`, `Body`, and `Air` decide which spectral zones are doing the pushing.
- `Band Mode` and the split controls decide whether those zones share one motion or get their own.

## Practical Starting Points

### 1. Gentle Breathing Motion

Good for pads, ambient guitars, Rhodes, and soft synths.

- `Band Mode`: `1 Band` or `2 Bands`
- `Amount`: `20-40%`
- `Speed`: `20-35%`
- `Chop`: `10-25%`
- `Sensitivity`: `25-45%`
- `Lift`: `30-55%`
- `Adaptive Mode`: `Off` or `On` with low `Adaptive Alpha`

This gives you a soft rise-and-fall rather than obvious tremolo.

### 2. Rhythmic Pumping

Good for synth buses, loops, and energetic productions.

- `Band Mode`: `1 Band` or `2 Bands`
- `Sync Mode`: `Synced`
- `Amount`: `50-80%`
- `Speed`: `45-75%`
- `Chop`: `40-70%`
- `Sensitivity`: `40-65%`
- `Lift`: `10-35%`

If it feels too soft, increase `Chop`. If it feels too extreme, lower `Amount` before anything else.

### 3. Low End Stable, Highs Animated

Good for mixes where you want excitement without the bass wobbling too much.

- `Band Mode`: `3 Bands`
- `Low`: `20-40%`
- `Body`: `45-60%`
- `Air`: `60-85%`
- `Low Split`: around `120-300 Hz`
- `High Split`: around `2-4 kHz`

This keeps the bottom more grounded while the top of the signal shimmers and dances.

### 4. Bass-Driven Movement

Good when you want kick and bass energy to lead the motion.

- `Band Mode`: `2 Bands` or `3 Bands`
- `Low`: `60-90%`
- `Body`: `40-55%`
- `Air`: `25-45%`
- `Sensitivity`: `50-75%`

If the whole mix starts lurching too much, lower `Amount` or reduce `Low`.

### 5. Nervous, Choppy Texture

Good for glitchier material, percussion, and aggressive synths.

- `Band Mode`: `2 Bands` or `3 Bands`
- `Amount`: `55-90%`
- `Speed`: `60-90%`
- `Chop`: `70-100%`
- `Sensitivity`: `65-100%`
- `Lift`: `0-20%`

This is where Surge starts sounding less like tremolo and more like reactive chopping.

### 6. Evolving Full-Mix Motion

Good on buses or full tracks, but start conservatively.

- `Band Mode`: `2 Bands`
- `Amount`: `15-35%`
- `Speed`: `25-45%`
- `Chop`: `20-40%`
- `Sensitivity`: `30-50%`
- `Lift`: `25-50%`
- `Adaptive Mode`: `On`
- `Adaptive Alpha`: `0.15-0.35`

For mix-bus use, less is usually better.

## Tips

- Start with `Amount` lower than you think you need, especially on full mixes.
- If the effect feels too random, lower `Sensitivity`.
- If the effect feels too flat, raise `Sensitivity` or raise one of `Low`, `Body`, or `Air`.
- If the lows are wobbling too much, lower `Low` or narrow the low band.
- If the top end is too fizzy or jumpy, lower `Air`.
- If the effect feels too hard-gated, lower `Chop` or raise `Lift`.
- `2 Bands` is often the easiest mode to mix because it gives separation without becoming overly complex.
- `3 Bands` is where the plugin becomes most expressive, but it is also easiest to overdo.
- If you want blend control, use Surge in parallel with your DAW's wet/dry or send routing, since the plugin itself is built around the motion engine rather than a dedicated mix knob.

## Troubleshooting By Ear

### "I barely hear it"

Try this:

- Raise `Amount`
- Raise `Sensitivity`
- Raise the relevant tone control for the part of the spectrum you want to react
- Move from `1 Band` to `2 Bands` or `3 Bands`

### "It is too twitchy"

Try this:

- Lower `Sensitivity`
- Lower `Air`
- Turn `Adaptive Mode` off
- Lower `Adaptive Alpha`

### "It sounds too choppy"

Try this:

- Lower `Chop`
- Raise `Lift`
- Lower `Amount`

### "The low end is moving too much"

Try this:

- Lower `Low`
- Use `2 Bands`
- Lower `Low Split`
- Lower `Amount`

## Suggested Workflow

1. Pick `1 Band`, `2 Bands`, or `3 Bands`.
2. Set the split points.
3. Set `Amount`.
4. Set `Speed`.
5. Decide whether the feel should be smooth or hard with `Chop`.
6. Set `Sensitivity`.
7. Use `Low`, `Body`, and `Air` to point the motion toward the part of the spectrum you want to feature.
8. Finish with `Lift`, then decide whether `Adaptive Mode` helps or hurts the source.

That order usually gets you to a useful sound faster than moving everything at once.
