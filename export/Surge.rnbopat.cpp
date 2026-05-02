/*******************************************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER $200k in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below $200k annual revenue or funding.

For entities with OVER $200k in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing@cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/10730637742483-RNBO-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
*******************************************************************************************************************/

#ifdef RNBO_LIB_PREFIX
#define STR_IMPL(A) #A
#define STR(A) STR_IMPL(A)
#define RNBO_LIB_INCLUDE(X) STR(RNBO_LIB_PREFIX/X)
#else
#define RNBO_LIB_INCLUDE(X) #X
#endif // RNBO_LIB_PREFIX
#ifdef RNBO_INJECTPLATFORM
#define RNBO_USECUSTOMPLATFORM
#include RNBO_INJECTPLATFORM
#endif // RNBO_INJECTPLATFORM

#include RNBO_LIB_INCLUDE(RNBO_Common.h)
#include RNBO_LIB_INCLUDE(RNBO_AudioSignal.h)

namespace RNBO {


#define trunc(x) ((Int)(x))
#define autoref auto&

#if defined(__GNUC__) || defined(__clang__)
    #define RNBO_RESTRICT __restrict__
#elif defined(_MSC_VER)
    #define RNBO_RESTRICT __restrict
#endif

#define FIXEDSIZEARRAYINIT(...) { }

template <class ENGINE = INTERNALENGINE> class rnbomatic : public PatcherInterfaceImpl {

friend class EngineCore;
friend class Engine;
friend class MinimalEngine<>;
public:

rnbomatic()
: _internalEngine(this)
{
}

~rnbomatic()
{
    deallocateSignals();
}

Index getNumMidiInputPorts() const {
    return 0;
}

void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}

Index getNumMidiOutputPorts() const {
    return 0;
}

void process(
    const SampleValue * const* inputs,
    Index numInputs,
    SampleValue * const* outputs,
    Index numOutputs,
    Index n
) {
    this->vs = n;
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
    SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
    SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
    const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
    const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
    this->signalsend_01_perform(in1, this->dummyBuffer, n);

    this->codebox_tilde_04_perform(
        this->codebox_tilde_04_in1,
        this->signals[0],
        this->signals[1],
        this->signals[2],
        n
    );

    this->signalsend_05_perform(in2, this->dummyBuffer, n);

    this->codebox_tilde_06_perform(
        this->codebox_tilde_06_in1,
        this->codebox_tilde_06_in2,
        this->signals[3],
        this->signals[4],
        n
    );

    this->signalsend_10_perform(this->signals[3], this->signals[5], n);
    this->signalreceive_02_perform(this->signals[5], this->signals[3], n);
    this->cross_tilde_03_perform(in2, this->signals[3], this->signals[6], this->signals[7], n);
    this->signalsend_06_perform(this->signals[6], this->signals[8], n);
    this->signalreceive_01_perform(this->signals[8], this->signals[6], n);
    this->dspexpr_09_perform(this->signals[6], this->dspexpr_09_in2, this->signals[9], n);
    this->signalreceive_12_perform(this->signals[8], this->signals[6], n);
    this->cross_tilde_01_perform(in1, this->signals[3], this->signals[8], this->signals[10], n);
    this->signalsend_02_perform(this->signals[8], this->signals[3], n);
    this->signalreceive_07_perform(this->signals[3], this->signals[11], n);
    this->dspexpr_07_perform(this->signals[8], this->dspexpr_07_in2, this->signals[3], n);
    this->dspexpr_08_perform(this->signals[3], this->signals[9], this->signals[8], n);
    this->signalreceive_15_perform(this->signals[5], this->signals[9], n);
    this->signalsend_11_perform(this->signals[4], this->signals[5], n);
    this->signalreceive_06_perform(this->signals[5], this->signals[4], n);
    this->cross_tilde_04_perform(this->signals[7], this->signals[4], this->signals[3], this->signals[12], n);
    this->signalsend_08_perform(this->signals[3], this->signals[7], n);
    this->signalreceive_04_perform(this->signals[7], this->signals[3], n);
    this->dspexpr_16_perform(this->signals[3], this->dspexpr_16_in2, this->signals[13], n);
    this->signalreceive_14_perform(this->signals[7], this->signals[3], n);
    this->signalsend_09_perform(this->signals[12], this->signals[7], n);
    this->signalreceive_10_perform(this->signals[7], this->signals[12], n);
    this->dspexpr_23_perform(this->signals[12], this->dspexpr_23_in2, this->signals[14], n);
    this->signalreceive_13_perform(this->signals[7], this->signals[12], n);

    this->cross_tilde_02_perform(
        this->signals[10],
        this->signals[4],
        this->signals[7],
        this->signals[15],
        n
    );

    this->signalsend_03_perform(this->signals[7], this->signals[4], n);
    this->signalreceive_03_perform(this->signals[4], this->signals[7], n);
    this->dspexpr_11_perform(this->signals[7], this->dspexpr_11_in2, this->signals[10], n);
    this->dspexpr_10_perform(this->signals[8], this->signals[10], this->signals[7], n);
    this->dspexpr_13_perform(this->signals[7], this->signals[13], this->signals[10], n);
    this->signalreceive_09_perform(this->signals[4], this->signals[13], n);
    this->signalsend_04_perform(this->signals[15], this->signals[4], n);
    this->signalreceive_05_perform(this->signals[4], this->signals[15], n);
    this->dspexpr_20_perform(this->signals[15], this->dspexpr_20_in2, this->signals[7], n);
    this->dspexpr_15_perform(this->signals[10], this->signals[7], this->signals[15], n);
    this->dspexpr_18_perform(this->signals[15], this->signals[14], this->signals[7], n);
    this->dspexpr_19_perform(this->signals[7], this->dspexpr_19_in2, this->signals[14], n);
    this->signalsend_07_perform(this->signals[14], this->signals[7], n);
    this->signalreceive_11_perform(this->signals[7], this->signals[14], n);
    this->signalreceive_08_perform(this->signals[4], this->signals[7], n);
    this->signalreceive_16_perform(this->signals[5], this->signals[4], n);

    this->p_01_perform(
        this->signals[14],
        this->signals[9],
        this->signals[4],
        this->signals[5],
        this->signals[15],
        this->signals[10],
        this->signals[8],
        this->signals[16],
        this->signals[17],
        this->signals[18],
        this->signals[19],
        this->signals[20],
        n
    );

    this->codebox_tilde_05_perform(
        this->codebox_tilde_05_in1,
        this->codebox_tilde_05_in2,
        this->codebox_tilde_05_in3,
        this->signals[5],
        this->signals[15],
        this->signals[10],
        this->signals[8],
        this->signals[16],
        this->signals[17],
        this->signals[18],
        this->signals[19],
        this->signals[20],
        this->codebox_tilde_05_in13,
        this->codebox_tilde_05_in14,
        this->signals[4],
        this->signals[9],
        this->signals[14],
        this->signals[21],
        this->signals[22],
        this->signals[23],
        this->signals[24],
        this->signals[25],
        this->signals[26],
        n
    );

    this->dspexpr_12_perform(this->signals[4], this->dspexpr_12_in2, this->signals[20], n);
    this->phasor_01_perform(this->signals[20], this->signals[4], n);

    this->selector_01_perform(
        this->selector_01_onoff,
        this->signals[4],
        this->signals[0],
        this->signals[20],
        n
    );

    this->dspexpr_14_perform(this->signals[9], this->dspexpr_14_in2, this->signals[0], n);
    this->phasor_02_perform(this->signals[0], this->signals[9], n);

    this->selector_02_perform(
        this->selector_02_onoff,
        this->signals[9],
        this->signals[1],
        this->signals[0],
        n
    );

    this->dspexpr_17_perform(this->signals[14], this->dspexpr_17_in2, this->signals[1], n);
    this->phasor_03_perform(this->signals[1], this->signals[14], n);

    this->selector_03_perform(
        this->selector_03_onoff,
        this->signals[14],
        this->signals[2],
        this->signals[1],
        n
    );

    this->dspexpr_37_perform(this->signals[21], this->dspexpr_37_in2, this->signals[2], n);
    this->dspexpr_36_perform(this->signals[2], this->dspexpr_36_in2, this->signals[14], n);

    this->dspexpr_35_perform(
        this->signals[14],
        this->dspexpr_35_in2,
        this->dspexpr_35_in3,
        this->signals[2],
        n
    );

    this->dspexpr_26_perform(this->signals[21], this->dspexpr_26_in2, this->signals[14], n);
    this->dspexpr_25_perform(this->signals[14], this->dspexpr_25_in2, this->signals[21], n);

    this->dspexpr_24_perform(
        this->signals[21],
        this->dspexpr_24_in2,
        this->dspexpr_24_in3,
        this->signals[14],
        n
    );

    this->dspexpr_40_perform(this->signals[22], this->dspexpr_40_in2, this->signals[21], n);
    this->dspexpr_39_perform(this->signals[21], this->dspexpr_39_in2, this->signals[9], n);

    this->dspexpr_38_perform(
        this->signals[9],
        this->dspexpr_38_in2,
        this->dspexpr_38_in3,
        this->signals[21],
        n
    );

    this->dspexpr_27_perform(this->signals[22], this->dspexpr_27_in2, this->signals[9], n);
    this->dspexpr_29_perform(this->signals[9], this->dspexpr_29_in2, this->signals[22], n);

    this->dspexpr_28_perform(
        this->signals[22],
        this->dspexpr_28_in2,
        this->dspexpr_28_in3,
        this->signals[9],
        n
    );

    this->dspexpr_43_perform(this->signals[23], this->dspexpr_43_in2, this->signals[22], n);
    this->dspexpr_42_perform(this->signals[22], this->dspexpr_42_in2, this->signals[4], n);

    this->dspexpr_41_perform(
        this->signals[4],
        this->dspexpr_41_in2,
        this->dspexpr_41_in3,
        this->signals[22],
        n
    );

    this->dspexpr_32_perform(this->signals[23], this->dspexpr_32_in2, this->signals[4], n);
    this->dspexpr_31_perform(this->signals[4], this->dspexpr_31_in2, this->signals[23], n);

    this->dspexpr_30_perform(
        this->signals[23],
        this->dspexpr_30_in2,
        this->dspexpr_30_in3,
        this->signals[4],
        n
    );

    this->dspexpr_45_perform(this->signals[24], this->dspexpr_45_in2, this->signals[23], n);

    this->dspexpr_44_perform(
        this->signals[23],
        this->dspexpr_44_in2,
        this->dspexpr_44_in3,
        this->signals[24],
        n
    );

    this->gen_04_perform(
        this->signals[6],
        this->signals[2],
        this->signals[20],
        this->signals[24],
        this->gen_04_in5,
        this->signals[23],
        n
    );

    this->gen_01_perform(
        this->signals[11],
        this->signals[14],
        this->signals[20],
        this->signals[24],
        this->gen_01_in5,
        this->signals[2],
        n
    );

    this->dspexpr_47_perform(this->signals[25], this->dspexpr_47_in2, this->signals[24], n);

    this->dspexpr_46_perform(
        this->signals[24],
        this->dspexpr_46_in2,
        this->dspexpr_46_in3,
        this->signals[25],
        n
    );

    this->gen_06_perform(
        this->signals[3],
        this->signals[21],
        this->signals[0],
        this->signals[25],
        this->gen_06_in5,
        this->signals[24],
        n
    );

    this->dspexpr_34_perform(this->signals[23], this->signals[24], this->signals[21], n);

    this->gen_03_perform(
        this->signals[13],
        this->signals[9],
        this->signals[0],
        this->signals[25],
        this->gen_03_in5,
        this->signals[24],
        n
    );

    this->dspexpr_22_perform(this->signals[2], this->signals[24], this->signals[25], n);
    this->dspexpr_49_perform(this->signals[26], this->dspexpr_49_in2, this->signals[24], n);

    this->dspexpr_48_perform(
        this->signals[24],
        this->dspexpr_48_in2,
        this->dspexpr_48_in3,
        this->signals[26],
        n
    );

    this->gen_05_perform(
        this->signals[12],
        this->signals[22],
        this->signals[1],
        this->signals[26],
        this->gen_05_in5,
        this->signals[24],
        n
    );

    this->dspexpr_33_perform(this->signals[21], this->signals[24], out2, n);

    this->gen_02_perform(
        this->signals[7],
        this->signals[4],
        this->signals[1],
        this->signals[26],
        this->gen_02_in5,
        this->signals[24],
        n
    );

    this->dspexpr_21_perform(this->signals[25], this->signals[24], out1, n);
    this->stackprotect_perform(n);
    this->globaltransport_advance();
    this->advanceTime((ENGINE*)nullptr);
    this->audioProcessSampleCount += this->vs;
}

void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
    RNBO_ASSERT(this->_isInitialized);

    if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
        Index i;

        for (i = 0; i < 27; i++) {
            this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
        }

        this->phasor_01_sigbuf = resizeSignal(this->phasor_01_sigbuf, this->maxvs, maxBlockSize);
        this->phasor_02_sigbuf = resizeSignal(this->phasor_02_sigbuf, this->maxvs, maxBlockSize);
        this->phasor_03_sigbuf = resizeSignal(this->phasor_03_sigbuf, this->maxvs, maxBlockSize);
        this->globaltransport_tempo = resizeSignal(this->globaltransport_tempo, this->maxvs, maxBlockSize);
        this->globaltransport_state = resizeSignal(this->globaltransport_state, this->maxvs, maxBlockSize);
        this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
        this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
        this->didAllocateSignals = true;
    }

    const bool sampleRateChanged = sampleRate != this->sr;
    const bool maxvsChanged = maxBlockSize != this->maxvs;
    const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;

    if (sampleRateChanged || maxvsChanged) {
        this->vs = maxBlockSize;
        this->maxvs = maxBlockSize;
        this->sr = sampleRate;
        this->invsr = 1 / sampleRate;
    }

    this->cross_tilde_03_dspsetup(forceDSPSetup);
    this->cross_tilde_01_dspsetup(forceDSPSetup);
    this->cross_tilde_04_dspsetup(forceDSPSetup);
    this->cross_tilde_02_dspsetup(forceDSPSetup);
    this->phasor_01_dspsetup(forceDSPSetup);
    this->phasor_02_dspsetup(forceDSPSetup);
    this->phasor_03_dspsetup(forceDSPSetup);
    this->globaltransport_dspsetup(forceDSPSetup);
    this->p_01->prepareToProcess(sampleRate, maxBlockSize, force);

    if (sampleRateChanged)
        this->onSampleRateChanged(sampleRate);
}

number msToSamps(MillisecondTime ms, number sampleRate) {
    return ms * sampleRate * 0.001;
}

MillisecondTime sampsToMs(SampleIndex samps) {
    return samps * (this->invsr * 1000);
}

Index getNumInputChannels() const {
    return 2;
}

Index getNumOutputChannels() const {
    return 2;
}

DataRef* getDataRef(DataRefIndex index)  {
    switch (index) {
    default:
        {
        return nullptr;
        }
    }
}

DataRefIndex getNumDataRefs() const {
    return 0;
}

void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
    this->p_01->processDataViewUpdate(index, time);
}

void initialize() {
    RNBO_ASSERT(!this->_isInitialized);
    this->assign_defaults();
    this->applyState();
    this->initializeObjects();
    this->allocateDataRefs();
    this->startup();
    this->_isInitialized = true;
}

void processTempoEvent(MillisecondTime time, Tempo tempo) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setTempo(this->_currentTime, tempo, false)) {
        this->p_01->processTempoEvent(time, tempo);
    }
}

void processTransportEvent(MillisecondTime time, TransportState state) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setState(this->_currentTime, state, false)) {
        this->p_01->processTransportEvent(time, state);
    }
}

void processBeatTimeEvent(MillisecondTime time, BeatTime beattime) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setBeatTime(this->_currentTime, beattime, false)) {
        this->p_01->processBeatTimeEvent(time, beattime);
        this->phasor_01_onBeatTimeChanged(beattime);
        this->phasor_02_onBeatTimeChanged(beattime);
        this->phasor_03_onBeatTimeChanged(beattime);
    }
}

void processTimeSignatureEvent(MillisecondTime time, Int numerator, Int denominator) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setTimeSignature(this->_currentTime, numerator, denominator, false)) {
        this->p_01->processTimeSignatureEvent(time, numerator, denominator);
    }
}

void processBBUEvent(MillisecondTime time, number bars, number beats, number units) {
    this->updateTime(time, (ENGINE*)nullptr);

    if (this->globaltransport_setBBU(this->_currentTime, bars, beats, units, false)) {
        this->p_01->processBBUEvent(time, bars, beats, units);
    }
}

void getPreset(PatcherStateInterface& preset) {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    preset["__presetid"] = "rnbo";
    this->param_01_getPresetValue(getSubState(preset, "amount"));
    this->param_02_getPresetValue(getSubState(preset, "speed"));
    this->param_03_getPresetValue(getSubState(preset, "band_surge"));
    this->param_04_getPresetValue(getSubState(preset, "sensitivity"));
    this->param_05_getPresetValue(getSubState(preset, "sync_mode"));
    this->param_06_getPresetValue(getSubState(preset, "lift"));
    this->param_07_getPresetValue(getSubState(preset, "chop"));
    this->param_08_getPresetValue(getSubState(preset, "low"));
    this->param_09_getPresetValue(getSubState(preset, "body"));
    this->param_10_getPresetValue(getSubState(preset, "air"));
    this->param_11_getPresetValue(getSubState(preset, "adaptive_mode"));
    this->param_12_getPresetValue(getSubState(preset, "low_split"));
    this->param_13_getPresetValue(getSubState(preset, "high_split"));
    this->param_14_getPresetValue(getSubState(preset, "adaptive_alpha"));
    this->p_01->getPreset(getSubState(getSubState(preset, "__sps"), "fft_analysis"));
}

void setPreset(MillisecondTime time, PatcherStateInterface& preset) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->p_01->setPreset(time, getSubState(getSubState(preset, "__sps"), "fft_analysis"));
    this->param_01_setPresetValue(getSubState(preset, "amount"));
    this->param_02_setPresetValue(getSubState(preset, "speed"));
    this->param_03_setPresetValue(getSubState(preset, "band_surge"));
    this->param_04_setPresetValue(getSubState(preset, "sensitivity"));
    this->param_05_setPresetValue(getSubState(preset, "sync_mode"));
    this->param_06_setPresetValue(getSubState(preset, "lift"));
    this->param_07_setPresetValue(getSubState(preset, "chop"));
    this->param_08_setPresetValue(getSubState(preset, "low"));
    this->param_09_setPresetValue(getSubState(preset, "body"));
    this->param_10_setPresetValue(getSubState(preset, "air"));
    this->param_11_setPresetValue(getSubState(preset, "adaptive_mode"));
    this->param_12_setPresetValue(getSubState(preset, "low_split"));
    this->param_13_setPresetValue(getSubState(preset, "high_split"));
    this->param_14_setPresetValue(getSubState(preset, "adaptive_alpha"));
}

void setParameterValue(ParameterIndex index, ParameterValue v, MillisecondTime time) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (index) {
    case 0:
        {
        this->param_01_value_set(v);
        break;
        }
    case 1:
        {
        this->param_02_value_set(v);
        break;
        }
    case 2:
        {
        this->param_03_value_set(v);
        break;
        }
    case 3:
        {
        this->param_04_value_set(v);
        break;
        }
    case 4:
        {
        this->param_05_value_set(v);
        break;
        }
    case 5:
        {
        this->param_06_value_set(v);
        break;
        }
    case 6:
        {
        this->param_07_value_set(v);
        break;
        }
    case 7:
        {
        this->param_08_value_set(v);
        break;
        }
    case 8:
        {
        this->param_09_value_set(v);
        break;
        }
    case 9:
        {
        this->param_10_value_set(v);
        break;
        }
    case 10:
        {
        this->param_11_value_set(v);
        break;
        }
    case 11:
        {
        this->param_12_value_set(v);
        break;
        }
    case 12:
        {
        this->param_13_value_set(v);
        break;
        }
    case 13:
        {
        this->param_14_value_set(v);
        break;
        }
    default:
        {
        index -= 14;

        if (index < this->p_01->getNumParameters())
            this->p_01->setParameterValue(index, v, time);

        break;
        }
    }
}

void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValue(index, value, time);
}

void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
    this->setParameterValue(index, this->getParameterValue(index), time);
}

void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
    this->setParameterValueNormalized(index, value, time);
}

ParameterValue getParameterValue(ParameterIndex index)  {
    switch (index) {
    case 0:
        {
        return this->param_01_value;
        }
    case 1:
        {
        return this->param_02_value;
        }
    case 2:
        {
        return this->param_03_value;
        }
    case 3:
        {
        return this->param_04_value;
        }
    case 4:
        {
        return this->param_05_value;
        }
    case 5:
        {
        return this->param_06_value;
        }
    case 6:
        {
        return this->param_07_value;
        }
    case 7:
        {
        return this->param_08_value;
        }
    case 8:
        {
        return this->param_09_value;
        }
    case 9:
        {
        return this->param_10_value;
        }
    case 10:
        {
        return this->param_11_value;
        }
    case 11:
        {
        return this->param_12_value;
        }
    case 12:
        {
        return this->param_13_value;
        }
    case 13:
        {
        return this->param_14_value;
        }
    default:
        {
        index -= 14;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterValue(index);

        return 0;
        }
    }
}

ParameterIndex getNumSignalInParameters() const {
    return 0;
}

ParameterIndex getNumSignalOutParameters() const {
    return 0;
}

ParameterIndex getNumParameters() const {
    return 14 + this->p_01->getNumParameters();
}

ConstCharPointer getParameterName(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "amount";
        }
    case 1:
        {
        return "speed";
        }
    case 2:
        {
        return "band_surge";
        }
    case 3:
        {
        return "sensitivity";
        }
    case 4:
        {
        return "sync_mode";
        }
    case 5:
        {
        return "lift";
        }
    case 6:
        {
        return "chop";
        }
    case 7:
        {
        return "low";
        }
    case 8:
        {
        return "body";
        }
    case 9:
        {
        return "air";
        }
    case 10:
        {
        return "adaptive_mode";
        }
    case 11:
        {
        return "low_split";
        }
    case 12:
        {
        return "high_split";
        }
    case 13:
        {
        return "adaptive_alpha";
        }
    default:
        {
        index -= 14;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterName(index);

        return "bogus";
        }
    }
}

ConstCharPointer getParameterId(ParameterIndex index) const {
    switch (index) {
    case 0:
        {
        return "amount";
        }
    case 1:
        {
        return "speed";
        }
    case 2:
        {
        return "band_surge";
        }
    case 3:
        {
        return "sensitivity";
        }
    case 4:
        {
        return "sync_mode";
        }
    case 5:
        {
        return "lift";
        }
    case 6:
        {
        return "chop";
        }
    case 7:
        {
        return "low";
        }
    case 8:
        {
        return "body";
        }
    case 9:
        {
        return "air";
        }
    case 10:
        {
        return "adaptive_mode";
        }
    case 11:
        {
        return "low_split";
        }
    case 12:
        {
        return "high_split";
        }
    case 13:
        {
        return "adaptive_alpha";
        }
    default:
        {
        index -= 14;

        if (index < this->p_01->getNumParameters())
            return this->p_01->getParameterId(index);

        return "bogus";
        }
    }
}

void getParameterInfo(ParameterIndex index, ParameterInfo * info) const {
    {
        switch (index) {
        case 0:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Surge Amount";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 1:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Speed";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 2:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal2[] = {"off", "on"};
            info->enumValues = eVal2;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Band Aware";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 3:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Sensitivity";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 4:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 1;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal4[] = {"free", "synced"};
            info->enumValues = eVal4;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Sync Mode";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 5:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Lift";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 6:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Chop";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 7:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Low";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 8:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Body";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 9:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.5;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Air";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 10:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0;
            info->min = 0;
            info->max = 1;
            info->exponent = 1;
            info->steps = 2;
            static const char * eVal10[] = {"off", "on"};
            info->enumValues = eVal10;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Adaptive Mode";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 11:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 800;
            info->min = 0;
            info->max = 4000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Low Split";
            info->unit = "Hz";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 12:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 2000;
            info->min = 0;
            info->max = 8000;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "High Split";
            info->unit = "Hz";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        case 13:
            {
            info->type = ParameterTypeNumber;
            info->initialValue = 0.3;
            info->min = 0.1;
            info->max = 0.9;
            info->exponent = 1;
            info->steps = 0;
            info->debug = false;
            info->saveable = true;
            info->transmittable = true;
            info->initialized = true;
            info->visible = true;
            info->displayName = "Adaptive Alpha";
            info->unit = "";
            info->ioType = IOTypeUndefined;
            info->signalIndex = INVALID_INDEX;
            break;
            }
        default:
            {
            index -= 14;

            if (index < this->p_01->getNumParameters())
                this->p_01->getParameterInfo(index, info);

            break;
            }
        }
    }
}

ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
    if (steps == 1) {
        if (normalizedValue > 0) {
            normalizedValue = 1.;
        }
    } else {
        ParameterValue oneStep = (number)1. / (steps - 1);
        ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
        normalizedValue = numberOfSteps * oneStep;
    }

    return normalizedValue;
}

ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
    case 1:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);
            return normalizedValue;
        }
        }
    case 2:
    case 4:
    case 10:
        {
        {
            value = (value < 0 ? 0 : (value > 1 ? 1 : value));
            ParameterValue normalizedValue = (value - 0) / (1 - 0);

            {
                normalizedValue = this->applyStepsToNormalizedParameterValue(normalizedValue, 2);
            }

            return normalizedValue;
        }
        }
    case 11:
        {
        {
            value = (value < 0 ? 0 : (value > 4000 ? 4000 : value));
            ParameterValue normalizedValue = (value - 0) / (4000 - 0);
            return normalizedValue;
        }
        }
    case 12:
        {
        {
            value = (value < 0 ? 0 : (value > 8000 ? 8000 : value));
            ParameterValue normalizedValue = (value - 0) / (8000 - 0);
            return normalizedValue;
        }
        }
    case 13:
        {
        {
            value = (value < 0.1 ? 0.1 : (value > 0.9 ? 0.9 : value));
            ParameterValue normalizedValue = (value - 0.1) / (0.9 - 0.1);
            return normalizedValue;
        }
        }
    default:
        {
        index -= 14;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertToNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
    value = (value < 0 ? 0 : (value > 1 ? 1 : value));

    switch (index) {
    case 0:
    case 1:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        {
        {
            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 2:
    case 4:
    case 10:
        {
        {
            {
                value = this->applyStepsToNormalizedParameterValue(value, 2);
            }

            {
                return 0 + value * (1 - 0);
            }
        }
        }
    case 11:
        {
        {
            {
                return 0 + value * (4000 - 0);
            }
        }
        }
    case 12:
        {
        {
            {
                return 0 + value * (8000 - 0);
            }
        }
        }
    case 13:
        {
        {
            {
                return 0.1 + value * (0.9 - 0.1);
            }
        }
        }
    default:
        {
        index -= 14;

        if (index < this->p_01->getNumParameters())
            return this->p_01->convertFromNormalizedParameterValue(index, value);

        return value;
        }
    }
}

ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
    switch (index) {
    case 0:
        {
        return this->param_01_value_constrain(value);
        }
    case 1:
        {
        return this->param_02_value_constrain(value);
        }
    case 2:
        {
        return this->param_03_value_constrain(value);
        }
    case 3:
        {
        return this->param_04_value_constrain(value);
        }
    case 4:
        {
        return this->param_05_value_constrain(value);
        }
    case 5:
        {
        return this->param_06_value_constrain(value);
        }
    case 6:
        {
        return this->param_07_value_constrain(value);
        }
    case 7:
        {
        return this->param_08_value_constrain(value);
        }
    case 8:
        {
        return this->param_09_value_constrain(value);
        }
    case 9:
        {
        return this->param_10_value_constrain(value);
        }
    case 10:
        {
        return this->param_11_value_constrain(value);
        }
    case 11:
        {
        return this->param_12_value_constrain(value);
        }
    case 12:
        {
        return this->param_13_value_constrain(value);
        }
    case 13:
        {
        return this->param_14_value_constrain(value);
        }
    default:
        {
        index -= 14;

        if (index < this->p_01->getNumParameters())
            return this->p_01->constrainParameterValue(index, value);

        return value;
        }
    }
}

void processNumMessage(MessageTag tag, MessageTag objectId, MillisecondTime time, number payload) {
    this->updateTime(time, (ENGINE*)nullptr);

    switch (tag) {
    case TAG("valin"):
        {
        if (TAG("number_obj-9") == objectId)
            this->numberobj_01_valin_set(payload);

        if (TAG("number_obj-1") == objectId)
            this->numberobj_02_valin_set(payload);

        if (TAG("number_obj-2") == objectId)
            this->numberobj_03_valin_set(payload);

        break;
        }
    case TAG("format"):
        {
        if (TAG("number_obj-9") == objectId)
            this->numberobj_01_format_set(payload);

        if (TAG("number_obj-1") == objectId)
            this->numberobj_02_format_set(payload);

        if (TAG("number_obj-2") == objectId)
            this->numberobj_03_format_set(payload);

        break;
        }
    }

    this->p_01->processNumMessage(tag, objectId, time, payload);
}

void processListMessage(
    MessageTag tag,
    MessageTag objectId,
    MillisecondTime time,
    const list& payload
) {
    RNBO_UNUSED(objectId);
    this->updateTime(time, (ENGINE*)nullptr);
    this->p_01->processListMessage(tag, objectId, time, payload);
}

void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
    RNBO_UNUSED(objectId);
    this->updateTime(time, (ENGINE*)nullptr);
    this->p_01->processBangMessage(tag, objectId, time);
}

MessageTagInfo resolveTag(MessageTag tag) const {
    switch (tag) {
    case TAG("valout"):
        {
        return "valout";
        }
    case TAG("number_obj-9"):
        {
        return "number_obj-9";
        }
    case TAG("setup"):
        {
        return "setup";
        }
    case TAG("number_obj-1"):
        {
        return "number_obj-1";
        }
    case TAG("number_obj-2"):
        {
        return "number_obj-2";
        }
    case TAG("valin"):
        {
        return "valin";
        }
    case TAG("format"):
        {
        return "format";
        }
    }

    auto subpatchResult_0 = this->p_01->resolveTag(tag);

    if (subpatchResult_0)
        return subpatchResult_0;

    return "";
}

MessageIndex getNumMessages() const {
    return 0;
}

const MessageInfo& getMessageInfo(MessageIndex index) const {
    switch (index) {

    }

    return NullMessageInfo;
}

protected:

class RNBOSubpatcher_60 : public PatcherInterfaceImpl {
    
    friend class rnbomatic;
    
    public:
    
    RNBOSubpatcher_60()
    {}
    
    ~RNBOSubpatcher_60()
    {
        deallocateSignals();
    }
    
    Index getNumMidiInputPorts() const {
        return 0;
    }
    
    void processMidiEvent(MillisecondTime , int , ConstByteArray , Index ) {}
    
    Index getNumMidiOutputPorts() const {
        return 0;
    }
    
    void process(
        const SampleValue * const* inputs,
        Index numInputs,
        SampleValue * const* outputs,
        Index numOutputs,
        Index n
    ) {
        this->vs = n;
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr, true);
        SampleValue * out1 = (numOutputs >= 1 && outputs[0] ? outputs[0] : this->dummyBuffer);
        SampleValue * out2 = (numOutputs >= 2 && outputs[1] ? outputs[1] : this->dummyBuffer);
        SampleValue * out3 = (numOutputs >= 3 && outputs[2] ? outputs[2] : this->dummyBuffer);
        SampleValue * out4 = (numOutputs >= 4 && outputs[3] ? outputs[3] : this->dummyBuffer);
        SampleValue * out5 = (numOutputs >= 5 && outputs[4] ? outputs[4] : this->dummyBuffer);
        SampleValue * out6 = (numOutputs >= 6 && outputs[5] ? outputs[5] : this->dummyBuffer);
        SampleValue * out7 = (numOutputs >= 7 && outputs[6] ? outputs[6] : this->dummyBuffer);
        SampleValue * out8 = (numOutputs >= 8 && outputs[7] ? outputs[7] : this->dummyBuffer);
        SampleValue * out9 = (numOutputs >= 9 && outputs[8] ? outputs[8] : this->dummyBuffer);
        const SampleValue * in1 = (numInputs >= 1 && inputs[0] ? inputs[0] : this->zeroBuffer);
        const SampleValue * in2 = (numInputs >= 2 && inputs[1] ? inputs[1] : this->zeroBuffer);
        const SampleValue * in3 = (numInputs >= 3 && inputs[2] ? inputs[2] : this->zeroBuffer);
    
        this->fftstream_tilde_01_perform(
            in1,
            this->fftstream_tilde_01_imagIn,
            this->signals[0],
            this->signals[1],
            this->signals[2],
            n
        );
    
        this->codebox_tilde_01_perform(
            this->signals[0],
            this->signals[1],
            this->signals[2],
            this->codebox_tilde_01_in4,
            this->codebox_tilde_01_in5,
            this->codebox_tilde_01_in6,
            this->codebox_tilde_01_in7,
            this->signals[3],
            this->signals[4],
            this->signals[5],
            n
        );
    
        this->slide_tilde_01_perform(
            this->signals[3],
            this->slide_tilde_01_up,
            this->slide_tilde_01_down,
            this->signals[2],
            n
        );
    
        this->dspexpr_01_perform(this->signals[2], this->dspexpr_01_in2, this->signals[3], n);
    
        this->dspexpr_02_perform(
            this->signals[3],
            this->dspexpr_02_in2,
            this->dspexpr_02_in3,
            this->signals[2],
            n
        );
    
        this->slide_tilde_02_perform(
            this->signals[4],
            this->slide_tilde_02_up,
            this->slide_tilde_02_down,
            this->signals[3],
            n
        );
    
        this->dspexpr_03_perform(this->signals[3], this->dspexpr_03_in2, this->signals[4], n);
    
        this->dspexpr_04_perform(
            this->signals[4],
            this->dspexpr_04_in2,
            this->dspexpr_04_in3,
            this->signals[3],
            n
        );
    
        this->slide_tilde_03_perform(
            this->signals[5],
            this->slide_tilde_03_up,
            this->slide_tilde_03_down,
            this->signals[4],
            n
        );
    
        this->dspexpr_05_perform(this->signals[4], this->dspexpr_05_in2, this->signals[5], n);
    
        this->dspexpr_06_perform(
            this->signals[5],
            this->dspexpr_06_in2,
            this->dspexpr_06_in3,
            this->signals[4],
            n
        );
    
        this->codebox_tilde_02_perform(
            this->signals[2],
            this->signals[3],
            this->signals[4],
            this->codebox_tilde_02_in4,
            this->signals[5],
            this->signals[1],
            this->signals[0],
            n
        );
    
        this->codebox_tilde_03_perform(
            this->signals[5],
            this->signals[1],
            this->signals[0],
            out1,
            out2,
            out3,
            out4,
            out5,
            out6,
            out7,
            out8,
            out9,
            n
        );
    
        this->stackprotect_perform(n);
        this->audioProcessSampleCount += this->vs;
    }
    
    void prepareToProcess(number sampleRate, Index maxBlockSize, bool force) {
        RNBO_ASSERT(this->_isInitialized);
    
        if (this->maxvs < maxBlockSize || !this->didAllocateSignals) {
            Index i;
    
            for (i = 0; i < 6; i++) {
                this->signals[i] = resizeSignal(this->signals[i], this->maxvs, maxBlockSize);
            }
    
            this->zeroBuffer = resizeSignal(this->zeroBuffer, this->maxvs, maxBlockSize);
            this->dummyBuffer = resizeSignal(this->dummyBuffer, this->maxvs, maxBlockSize);
            this->didAllocateSignals = true;
        }
    
        const bool sampleRateChanged = sampleRate != this->sr;
        const bool maxvsChanged = maxBlockSize != this->maxvs;
        const bool forceDSPSetup = sampleRateChanged || maxvsChanged || force;
    
        if (sampleRateChanged || maxvsChanged) {
            this->vs = maxBlockSize;
            this->maxvs = maxBlockSize;
            this->sr = sampleRate;
            this->invsr = 1 / sampleRate;
        }
    
        this->fftstream_tilde_01_dspsetup(forceDSPSetup);
        this->samplerate_01_dspsetup(forceDSPSetup);
    
        if (sampleRateChanged)
            this->onSampleRateChanged(sampleRate);
    }
    
    number msToSamps(MillisecondTime ms, number sampleRate) {
        return ms * sampleRate * 0.001;
    }
    
    MillisecondTime sampsToMs(SampleIndex samps) {
        return samps * (this->invsr * 1000);
    }
    
    Index getNumInputChannels() const {
        return 3;
    }
    
    Index getNumOutputChannels() const {
        return 9;
    }
    
    void getPreset(PatcherStateInterface& ) {}
    
    void setPreset(MillisecondTime , PatcherStateInterface& ) {}
    
    void setParameterValue(ParameterIndex , ParameterValue , MillisecondTime ) {}
    
    void processParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValue(index, value, time);
    }
    
    void processParameterBangEvent(ParameterIndex index, MillisecondTime time) {
        this->setParameterValue(index, this->getParameterValue(index), time);
    }
    
    void processNormalizedParameterEvent(ParameterIndex index, ParameterValue value, MillisecondTime time) {
        this->setParameterValueNormalized(index, value, time);
    }
    
    ParameterValue getParameterValue(ParameterIndex index)  {
        switch (index) {
        default:
            {
            return 0;
            }
        }
    }
    
    ParameterIndex getNumSignalInParameters() const {
        return 0;
    }
    
    ParameterIndex getNumSignalOutParameters() const {
        return 0;
    }
    
    ParameterIndex getNumParameters() const {
        return 0;
    }
    
    ConstCharPointer getParameterName(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    ConstCharPointer getParameterId(ParameterIndex index) const {
        switch (index) {
        default:
            {
            return "bogus";
            }
        }
    }
    
    void getParameterInfo(ParameterIndex , ParameterInfo * ) const {}
    
    ParameterValue applyStepsToNormalizedParameterValue(ParameterValue normalizedValue, int steps) const {
        if (steps == 1) {
            if (normalizedValue > 0) {
                normalizedValue = 1.;
            }
        } else {
            ParameterValue oneStep = (number)1. / (steps - 1);
            ParameterValue numberOfSteps = rnbo_fround(normalizedValue / oneStep * 1 / (number)1) * (number)1;
            normalizedValue = numberOfSteps * oneStep;
        }
    
        return normalizedValue;
    }
    
    ParameterValue convertToNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue convertFromNormalizedParameterValue(ParameterIndex index, ParameterValue value) const {
        value = (value < 0 ? 0 : (value > 1 ? 1 : value));
    
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    ParameterValue constrainParameterValue(ParameterIndex index, ParameterValue value) const {
        switch (index) {
        default:
            {
            return value;
            }
        }
    }
    
    void processNumMessage(MessageTag , MessageTag , MillisecondTime , number ) {}
    
    void processListMessage(MessageTag , MessageTag , MillisecondTime , const list& ) {}
    
    void processBangMessage(MessageTag tag, MessageTag objectId, MillisecondTime time) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (tag) {
        case TAG("startupbang"):
            {
            if (TAG("fft_analysis/loadbang_obj-53") == objectId)
                this->loadbang_01_startupbang_bang();
    
            break;
            }
        }
    }
    
    MessageTagInfo resolveTag(MessageTag tag) const {
        switch (tag) {
        case TAG("startupbang"):
            {
            return "startupbang";
            }
        case TAG("fft_analysis/loadbang_obj-53"):
            {
            return "fft_analysis/loadbang_obj-53";
            }
        }
    
        return nullptr;
    }
    
    DataRef* getDataRef(DataRefIndex index)  {
        switch (index) {
        case 0:
            {
            return addressOf(this->fftstream_tilde_01_win_bufobj);
            break;
            }
        default:
            {
            return nullptr;
            }
        }
    }
    
    DataRefIndex getNumDataRefs() const {
        return 1;
    }
    
    void processDataViewUpdate(DataRefIndex index, MillisecondTime time) {
        this->updateTime(time, (ENGINE*)nullptr);
    
        if (index == 0) {
            this->fftstream_tilde_01_win_buf = reInitDataView(this->fftstream_tilde_01_win_buf, this->fftstream_tilde_01_win_bufobj);
        }
    }
    
    void initialize() {
        RNBO_ASSERT(!this->_isInitialized);
    
        this->fftstream_tilde_01_win_bufobj = initDataRef(
            this->fftstream_tilde_01_win_bufobj,
            this->dataRefStrings->name0,
            true,
            this->dataRefStrings->file0,
            this->dataRefStrings->tag0
        );
    
        this->assign_defaults();
        this->applyState();
        this->fftstream_tilde_01_win_bufobj->setIndex(0);
        this->fftstream_tilde_01_win_buf = new SampleBuffer(this->fftstream_tilde_01_win_bufobj);
        this->_isInitialized = true;
    }
    
    protected:
    
    void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
    	if (time == TimeNow) time = getTopLevelPatcher()->getPatcherTime();
    	getTopLevelPatcher()->processInternalEvents(time);
    	updateTime(time, (EXTERNALENGINE*)nullptr);
    }
    
    RNBOSubpatcher_60* operator->() {
        return this;
    }
    const RNBOSubpatcher_60* operator->() const {
        return this;
    }
    virtual rnbomatic* getPatcher() const {
        return static_cast<rnbomatic *>(_parentPatcher);
    }
    
    rnbomatic* getTopLevelPatcher() {
        return this->getPatcher()->getTopLevelPatcher();
    }
    
    void cancelClockEvents()
    {
        getEngine()->flushClockEvents(this, -871642103, false);
    }
    
    number hann(number x) {
        x = (x > 1 ? 1 : (x < 0 ? 0 : x));
        return 0.5 * (1 - rnbo_cos(6.28318530717958647692 * x));
    }
    
    inline number safesqrt(number num) {
        return (num > 0.0 ? rnbo_sqrt(num) : 0.0);
    }
    
    array<number, 2> cartopol(number x, number y) {
        return {this->safesqrt(x * x + y * y), rnbo_atan2(y, x)};
    }
    
    number maximum(number x, number y) {
        return (x < y ? y : x);
    }
    
    inline number safediv(number num, number denom) {
        return (denom == 0.0 ? 0.0 : num / denom);
    }
    
    MillisecondTime getPatcherTime() const {
        return this->_currentTime;
    }
    
    void loadbang_01_startupbang_bang() {
        this->loadbang_01_output_bang();
    }
    
    void deallocateSignals() {
        Index i;
    
        for (i = 0; i < 6; i++) {
            this->signals[i] = freeSignal(this->signals[i]);
        }
    
        this->zeroBuffer = freeSignal(this->zeroBuffer);
        this->dummyBuffer = freeSignal(this->dummyBuffer);
    }
    
    Index getMaxBlockSize() const {
        return this->maxvs;
    }
    
    number getSampleRate() const {
        return this->sr;
    }
    
    bool hasFixedVectorSize() const {
        return false;
    }
    
    void setProbingTarget(MessageTag ) {}
    
    void initializeObjects() {}
    
    Index getIsMuted()  {
        return this->isMuted;
    }
    
    void setIsMuted(Index v)  {
        this->isMuted = v;
    }
    
    void onSampleRateChanged(double samplerate) {
        this->samplerate_01_onSampleRateChanged(samplerate);
    }
    
    void extractState(PatcherStateInterface& ) {}
    
    void applyState() {}
    
    void setParameterOffset(ParameterIndex offset) {
        this->parameterOffset = offset;
    }
    
    void processClockEvent(MillisecondTime time, ClockId index, bool hasValue, ParameterValue value) {
        RNBO_UNUSED(value);
        RNBO_UNUSED(hasValue);
        this->updateTime(time, (ENGINE*)nullptr);
    
        switch (index) {
        case -871642103:
            {
            this->loadbang_01_startupbang_bang();
            break;
            }
        }
    }
    
    void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}
    
    void processOutletEvent(
        EngineLink* sender,
        OutletIndex index,
        ParameterValue value,
        MillisecondTime time
    ) {
        this->updateTime(time, (ENGINE*)nullptr);
        this->processOutletAtCurrentTime(sender, index, value);
    }
    
    void sendOutlet(OutletIndex index, ParameterValue value) {
        this->getEngine()->sendOutlet(this, index, value);
    }
    
    void startup() {
        this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
        this->getEngine()->scheduleClockEvent(this, -871642103, 0 + this->_currentTime);;
    }
    
    void fillDataRef(DataRefIndex , DataRef& ) {}
    
    void zeroDataRef(DataRef& ref) {
        ref->setZero();
    }
    
    void allocateDataRefs() {
        this->fftstream_tilde_01_win_buf = this->fftstream_tilde_01_win_buf->allocateIfNeeded();
    
        if (this->fftstream_tilde_01_win_bufobj->hasRequestedSize()) {
            if (this->fftstream_tilde_01_win_bufobj->wantsFill())
                this->zeroDataRef(this->fftstream_tilde_01_win_bufobj);
    
            this->getEngine()->sendDataRefUpdated(0);
        }
    }
    
    void dspexpr_05_in2_set(number v) {
        this->dspexpr_05_in2 = v;
    }
    
    void dspexpr_03_in2_set(number v) {
        this->dspexpr_03_in2 = v;
    }
    
    void dspexpr_01_in2_set(number v) {
        this->dspexpr_01_in2 = v;
    }
    
    void expr_04_out1_set(number v) {
        this->expr_04_out1 = v;
        this->dspexpr_05_in2_set(this->expr_04_out1);
        this->dspexpr_03_in2_set(this->expr_04_out1);
        this->dspexpr_01_in2_set(this->expr_04_out1);
    }
    
    void expr_04_in1_set(number in1) {
        this->expr_04_in1 = in1;
        this->expr_04_out1_set(this->expr_04_in1 + this->expr_04_in2);//#map:fft_analysis/+_obj-79:1
    }
    
    void receive_01_output_number_set(number v) {
        this->receive_01_output_number = v;
        this->expr_04_in1_set(v);
    }
    
    void codebox_tilde_02_in4_set(number v) {
        this->codebox_tilde_02_in4 = v;
    }
    
    void receive_03_output_number_set(number v) {
        this->receive_03_output_number = v;
        this->codebox_tilde_02_in4_set(v);
    }
    
    void codebox_tilde_01_in6_set(number v) {
        this->codebox_tilde_01_in6 = v;
    }
    
    void receive_02_output_number_set(number v) {
        this->receive_02_output_number = v;
        this->codebox_tilde_01_in6_set(v);
    }
    
    void codebox_tilde_01_in7_set(number v) {
        this->codebox_tilde_01_in7 = v;
    }
    
    void receive_04_output_number_set(number v) {
        this->receive_04_output_number = v;
        this->codebox_tilde_01_in7_set(v);
    }
    
    void expr_07_in2_set(number v) {
        this->expr_07_in2 = v;
    }
    
    void expr_03_in2_set(number v) {
        this->expr_03_in2 = v;
    }
    
    void expr_08_out1_set(number v) {
        this->expr_08_out1 = v;
        this->expr_07_in2_set(this->expr_08_out1);
        this->expr_03_in2_set(this->expr_08_out1);
    }
    
    void expr_08_in1_set(number in1) {
        this->expr_08_in1 = in1;
    
        this->expr_08_out1_set(
            (this->expr_08_in2 == 0 ? 0 : (this->expr_08_in2 == 0. ? 0. : this->expr_08_in1 / this->expr_08_in2))
        );//#map:fft_analysis//_obj-47:1
    }
    
    void samplerate_01_samplerate_set(number v) {
        this->samplerate_01_samplerate = v;
        this->expr_08_in1_set(v);
    }
    
    void samplerate_01_input_bang() {
        this->samplerate_01_samplerate_set(this->sr);
    }
    
    void loadbang_01_output_bang() {
        this->samplerate_01_input_bang();
    }
    
    void fftstream_tilde_01_perform(
        const Sample * realIn,
        number imagIn,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        Index n
    ) {
        RNBO_UNUSED(imagIn);
        auto __fftstream_tilde_01_datapos = this->fftstream_tilde_01_datapos;
        number invFftSize = (number)1 / (number)1024;
        Index i0;
    
        for (i0 = 0; i0 < (Index)n; i0++) {
            SampleIndex i = (SampleIndex)(__fftstream_tilde_01_datapos);
            array<number, 3> out = {0, 0, i};
            number windowFactor = 1;
            windowFactor = this->hann(i * invFftSize);
    
            if (__fftstream_tilde_01_datapos < 1024) {
                this->fftstream_tilde_01_inWorkspace[(Index)(2 * i)] = windowFactor * realIn[(Index)i0];
                out[0] = this->fftstream_tilde_01_outWorkspace[(Index)(2 * i)];
                this->fftstream_tilde_01_inWorkspace[(Index)(2 * i + 1)] = windowFactor * 0;
                out[1] = this->fftstream_tilde_01_outWorkspace[(Index)(2 * i + 1)];
    
                if (i == 1024 - 1) {
                    this->fftstream_tilde_01_fft_next(this->fftstream_tilde_01_inWorkspace, 1024);
    
                    for (SampleIndex j = 0; j < 1024 * 2; j++) {
                        this->fftstream_tilde_01_outWorkspace[(Index)j] = this->fftstream_tilde_01_inWorkspace[(Index)j];
                    }
                }
    
                __fftstream_tilde_01_datapos = (__fftstream_tilde_01_datapos + 1) % 1024;
            }
    
            out1[(Index)i0] = out[0];
            out2[(Index)i0] = out[1];
            out3[(Index)i0] = out[2];
        }
    
        this->fftstream_tilde_01_datapos = __fftstream_tilde_01_datapos;
    }
    
    void codebox_tilde_01_perform(
        const Sample * in1,
        const Sample * in2,
        const Sample * in3,
        number in4,
        number in5,
        number in6,
        number in7,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        Index n
    ) {
        auto __codebox_tilde_01_heldHighDrive = this->codebox_tilde_01_heldHighDrive;
        auto __codebox_tilde_01_heldMidDrive = this->codebox_tilde_01_heldMidDrive;
        auto __codebox_tilde_01_heldLowDrive = this->codebox_tilde_01_heldLowDrive;
        auto __codebox_tilde_01_heldHighMotion = this->codebox_tilde_01_heldHighMotion;
        auto __codebox_tilde_01_heldMidMotion = this->codebox_tilde_01_heldMidMotion;
        auto __codebox_tilde_01_heldLowMotion = this->codebox_tilde_01_heldLowMotion;
        auto __codebox_tilde_01_heldHighShare = this->codebox_tilde_01_heldHighShare;
        auto __codebox_tilde_01_heldMidShare = this->codebox_tilde_01_heldMidShare;
        auto __codebox_tilde_01_heldLowShare = this->codebox_tilde_01_heldLowShare;
        auto __codebox_tilde_01_heldBaseHighIndex = this->codebox_tilde_01_heldBaseHighIndex;
        auto __codebox_tilde_01_heldBaseLowIndex = this->codebox_tilde_01_heldBaseLowIndex;
        auto __codebox_tilde_01_heldSpread = this->codebox_tilde_01_heldSpread;
        auto __codebox_tilde_01_heldCentroid = this->codebox_tilde_01_heldCentroid;
        auto __codebox_tilde_01_highFrameSum = this->codebox_tilde_01_highFrameSum;
        auto __codebox_tilde_01_midFrameSum = this->codebox_tilde_01_midFrameSum;
        auto __codebox_tilde_01_lowFrameSum = this->codebox_tilde_01_lowFrameSum;
        auto __codebox_tilde_01_weightedFrameSq = this->codebox_tilde_01_weightedFrameSq;
        auto __codebox_tilde_01_weightedFrameSum = this->codebox_tilde_01_weightedFrameSum;
        auto __codebox_tilde_01_frameSum = this->codebox_tilde_01_frameSum;
        auto __codebox_tilde_01_prevBinIndex = this->codebox_tilde_01_prevBinIndex;
        auto __codebox_tilde_01_adaptiveHighIndex = this->codebox_tilde_01_adaptiveHighIndex;
        auto __codebox_tilde_01_adaptiveLowIndex = this->codebox_tilde_01_adaptiveLowIndex;
        number lowSplitIndex = in4;
        number highSplitIndex = in5;
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            number MIN_INDEX = 2;
            number MAX_INDEX = 171;
            number real = in1[(Index)i];
            number imaginary = in2[(Index)i];
            number binIndex = in3[(Index)i];
            number adaptiveModeEnabled = in6;
            number adaptiveAlpha = in7;
            number lowIndex = lowSplitIndex;
            number highIndex = highSplitIndex;
    
            if ((bool)(adaptiveModeEnabled)) {
                lowIndex = rnbo_fround(__codebox_tilde_01_adaptiveLowIndex * 1 / (number)1) * 1;//#map:_###_obj_###_:65
                highIndex = rnbo_fround(__codebox_tilde_01_adaptiveHighIndex * 1 / (number)1) * 1;//#map:_###_obj_###_:66
            }//#map:_###_obj_###_:64
    
            auto polar = this->cartopol(real, imaginary);
            number magnitude = polar[0];
            number energy = magnitude * magnitude;
            number frameWrap = binIndex < __codebox_tilde_01_prevBinIndex;
            number binMask = (binIndex >= MIN_INDEX) * (binIndex <= MAX_INDEX);
            number binEnergy = energy * binMask;
            __codebox_tilde_01_frameSum = __codebox_tilde_01_frameSum + binEnergy;//#map:_###_obj_###_:79
            __codebox_tilde_01_weightedFrameSum = __codebox_tilde_01_weightedFrameSum + binEnergy * binIndex;//#map:_###_obj_###_:80
            __codebox_tilde_01_weightedFrameSq = __codebox_tilde_01_weightedFrameSq + binEnergy * binIndex * binIndex;//#map:_###_obj_###_:81
            number lowMask = (binIndex >= MIN_INDEX) * (binIndex <= lowIndex);
            number midMask = (binIndex >= lowIndex + 1) * (binIndex <= highIndex);
            number highMask = (binIndex >= highIndex + 1) * (binIndex <= MAX_INDEX);
            __codebox_tilde_01_lowFrameSum = __codebox_tilde_01_lowFrameSum + energy * lowMask;//#map:_###_obj_###_:88
            __codebox_tilde_01_midFrameSum = __codebox_tilde_01_midFrameSum + energy * midMask;//#map:_###_obj_###_:89
            __codebox_tilde_01_highFrameSum = __codebox_tilde_01_highFrameSum + energy * highMask;//#map:_###_obj_###_:90
    
            if ((bool)(frameWrap)) {
                if (__codebox_tilde_01_frameSum > 0.001) {
                    __codebox_tilde_01_frameSum = __codebox_tilde_01_frameSum + 1e-12;//#map:_###_obj_###_:96
                    number centroid = (__codebox_tilde_01_frameSum == 0. ? 0. : __codebox_tilde_01_weightedFrameSum / __codebox_tilde_01_frameSum);
                    number meanBinSq = (__codebox_tilde_01_frameSum == 0. ? 0. : __codebox_tilde_01_weightedFrameSq / __codebox_tilde_01_frameSum);
                    auto variance = this->maximum(0, meanBinSq - centroid * centroid);
                    number spread = (variance <= 0 ? 0 : rnbo_sqrt(variance));
                    number baseLowIndex = rnbo_floor(centroid - spread);
                    number baseHighIndex = rnbo_floor(centroid + spread);
                    baseLowIndex = (baseLowIndex > MAX_INDEX - 2 ? MAX_INDEX - 2 : (baseLowIndex < MIN_INDEX ? MIN_INDEX : baseLowIndex));//#map:_###_obj_###_:105
                    baseHighIndex = (baseHighIndex > MAX_INDEX - 1 ? MAX_INDEX - 1 : (baseHighIndex < MIN_INDEX + 1 ? MIN_INDEX + 1 : baseHighIndex));//#map:_###_obj_###_:106
    
                    if (baseHighIndex <= baseLowIndex) {
                        baseHighIndex = baseLowIndex + 1;//#map:_###_obj_###_:109
                    }//#map:_###_obj_###_:108
    
                    __codebox_tilde_01_heldCentroid = centroid;//#map:_###_obj_###_:112
                    __codebox_tilde_01_heldSpread = spread;//#map:_###_obj_###_:113
                    __codebox_tilde_01_heldBaseLowIndex = baseLowIndex;//#map:_###_obj_###_:114
                    __codebox_tilde_01_heldBaseHighIndex = baseHighIndex;//#map:_###_obj_###_:115
                    __codebox_tilde_01_adaptiveLowIndex = __codebox_tilde_01_adaptiveLowIndex + adaptiveAlpha * (baseLowIndex - __codebox_tilde_01_adaptiveLowIndex);//#map:_###_obj_###_:118
                    __codebox_tilde_01_adaptiveHighIndex = __codebox_tilde_01_adaptiveHighIndex + adaptiveAlpha * (baseHighIndex - __codebox_tilde_01_adaptiveHighIndex);//#map:_###_obj_###_:119
                }//#map:_###_obj_###_:94
    
                number total = __codebox_tilde_01_lowFrameSum + __codebox_tilde_01_midFrameSum + __codebox_tilde_01_highFrameSum + 1e-12;
                number newLowShare = (total == 0. ? 0. : __codebox_tilde_01_lowFrameSum / total);
                number newMidShare = (total == 0. ? 0. : __codebox_tilde_01_midFrameSum / total);
                number newHighShare = (total == 0. ? 0. : __codebox_tilde_01_highFrameSum / total);
                number newLowMotion = rnbo_abs(newLowShare - __codebox_tilde_01_heldLowShare);
                number newMidMotion = rnbo_abs(newMidShare - __codebox_tilde_01_heldMidShare);
                number newHighMotion = rnbo_abs(newHighShare - __codebox_tilde_01_heldHighShare);
                __codebox_tilde_01_heldLowMotion = newLowMotion;//#map:_###_obj_###_:133
                __codebox_tilde_01_heldMidMotion = newMidMotion;//#map:_###_obj_###_:134
                __codebox_tilde_01_heldHighMotion = newHighMotion;//#map:_###_obj_###_:135
                __codebox_tilde_01_heldLowShare = newLowShare;//#map:_###_obj_###_:137
                __codebox_tilde_01_heldMidShare = newMidShare;//#map:_###_obj_###_:138
                __codebox_tilde_01_heldHighShare = newHighShare;//#map:_###_obj_###_:139
                __codebox_tilde_01_heldLowDrive = (newLowShare * 0.35 + newLowMotion * 4 > 1 ? 1 : (newLowShare * 0.35 + newLowMotion * 4 < 0 ? 0 : newLowShare * 0.35 + newLowMotion * 4));//#map:_###_obj_###_:141
                __codebox_tilde_01_heldMidDrive = (newMidShare * 0.3 + newMidMotion * 6 > 1 ? 1 : (newMidShare * 0.3 + newMidMotion * 6 < 0 ? 0 : newMidShare * 0.3 + newMidMotion * 6));//#map:_###_obj_###_:147
                __codebox_tilde_01_heldHighDrive = (newHighShare * 0.45 + newHighMotion * 8 > 1 ? 1 : (newHighShare * 0.45 + newHighMotion * 8 < 0 ? 0 : newHighShare * 0.45 + newHighMotion * 8));//#map:_###_obj_###_:153
                __codebox_tilde_01_frameSum = 0;//#map:_###_obj_###_:160
                __codebox_tilde_01_weightedFrameSum = 0;//#map:_###_obj_###_:161
                __codebox_tilde_01_weightedFrameSq = 0;//#map:_###_obj_###_:162
                __codebox_tilde_01_lowFrameSum = 0;//#map:_###_obj_###_:164
                __codebox_tilde_01_midFrameSum = 0;//#map:_###_obj_###_:165
                __codebox_tilde_01_highFrameSum = 0;//#map:_###_obj_###_:166
            }//#map:_###_obj_###_:93
    
            out1[(Index)i] = __codebox_tilde_01_heldLowDrive;//#map:_###_obj_###_:169
            out2[(Index)i] = __codebox_tilde_01_heldMidDrive;//#map:_###_obj_###_:170
            out3[(Index)i] = __codebox_tilde_01_heldHighDrive;//#map:_###_obj_###_:171
            __codebox_tilde_01_prevBinIndex = binIndex;//#map:_###_obj_###_:173
        }
    
        this->codebox_tilde_01_adaptiveLowIndex = __codebox_tilde_01_adaptiveLowIndex;
        this->codebox_tilde_01_adaptiveHighIndex = __codebox_tilde_01_adaptiveHighIndex;
        this->codebox_tilde_01_prevBinIndex = __codebox_tilde_01_prevBinIndex;
        this->codebox_tilde_01_frameSum = __codebox_tilde_01_frameSum;
        this->codebox_tilde_01_weightedFrameSum = __codebox_tilde_01_weightedFrameSum;
        this->codebox_tilde_01_weightedFrameSq = __codebox_tilde_01_weightedFrameSq;
        this->codebox_tilde_01_lowFrameSum = __codebox_tilde_01_lowFrameSum;
        this->codebox_tilde_01_midFrameSum = __codebox_tilde_01_midFrameSum;
        this->codebox_tilde_01_highFrameSum = __codebox_tilde_01_highFrameSum;
        this->codebox_tilde_01_heldCentroid = __codebox_tilde_01_heldCentroid;
        this->codebox_tilde_01_heldSpread = __codebox_tilde_01_heldSpread;
        this->codebox_tilde_01_heldBaseLowIndex = __codebox_tilde_01_heldBaseLowIndex;
        this->codebox_tilde_01_heldBaseHighIndex = __codebox_tilde_01_heldBaseHighIndex;
        this->codebox_tilde_01_heldLowShare = __codebox_tilde_01_heldLowShare;
        this->codebox_tilde_01_heldMidShare = __codebox_tilde_01_heldMidShare;
        this->codebox_tilde_01_heldHighShare = __codebox_tilde_01_heldHighShare;
        this->codebox_tilde_01_heldLowMotion = __codebox_tilde_01_heldLowMotion;
        this->codebox_tilde_01_heldMidMotion = __codebox_tilde_01_heldMidMotion;
        this->codebox_tilde_01_heldHighMotion = __codebox_tilde_01_heldHighMotion;
        this->codebox_tilde_01_heldLowDrive = __codebox_tilde_01_heldLowDrive;
        this->codebox_tilde_01_heldMidDrive = __codebox_tilde_01_heldMidDrive;
        this->codebox_tilde_01_heldHighDrive = __codebox_tilde_01_heldHighDrive;
    }
    
    void slide_tilde_01_perform(const Sample * x, number up, number down, SampleValue * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_01_prev = this->slide_tilde_01_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(400)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(2200)));
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            number temp = x[(Index)i] - __slide_tilde_01_prev;
            __slide_tilde_01_prev = __slide_tilde_01_prev + ((x[(Index)i] > __slide_tilde_01_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_01_prev;
        }
    
        this->slide_tilde_01_prev = __slide_tilde_01_prev;
    }
    
    void dspexpr_01_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_02_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
        RNBO_UNUSED(in3);
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < 0 ? 0 : in1[(Index)i]));//#map:_###_obj_###_:1
        }
    }
    
    void slide_tilde_02_perform(const Sample * x, number up, number down, SampleValue * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_02_prev = this->slide_tilde_02_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(220)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(1400)));
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            number temp = x[(Index)i] - __slide_tilde_02_prev;
            __slide_tilde_02_prev = __slide_tilde_02_prev + ((x[(Index)i] > __slide_tilde_02_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_02_prev;
        }
    
        this->slide_tilde_02_prev = __slide_tilde_02_prev;
    }
    
    void dspexpr_03_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_04_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
        RNBO_UNUSED(in3);
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < 0 ? 0 : in1[(Index)i]));//#map:_###_obj_###_:1
        }
    }
    
    void slide_tilde_03_perform(const Sample * x, number up, number down, SampleValue * out1, Index n) {
        RNBO_UNUSED(down);
        RNBO_UNUSED(up);
        auto __slide_tilde_03_prev = this->slide_tilde_03_prev;
        auto iup = this->safediv(1., this->maximum(1., rnbo_abs(90)));
        auto idown = this->safediv(1., this->maximum(1., rnbo_abs(900)));
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            number temp = x[(Index)i] - __slide_tilde_03_prev;
            __slide_tilde_03_prev = __slide_tilde_03_prev + ((x[(Index)i] > __slide_tilde_03_prev ? iup : idown)) * temp;
            out1[(Index)i] = __slide_tilde_03_prev;
        }
    
        this->slide_tilde_03_prev = __slide_tilde_03_prev;
    }
    
    void dspexpr_05_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
        }
    }
    
    void dspexpr_06_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
        RNBO_UNUSED(in3);
        RNBO_UNUSED(in2);
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            out1[(Index)i] = (in1[(Index)i] > 1 ? 1 : (in1[(Index)i] < 0 ? 0 : in1[(Index)i]));//#map:_###_obj_###_:1
        }
    }
    
    void codebox_tilde_02_perform(
        const Sample * in1,
        const Sample * in2,
        const Sample * in3,
        number in4,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        Index n
    ) {
        number lift = in4;
        number floor = 0.2 * lift * lift;
        number oneMinusFloor = 1 - floor;
        number curveExp = 1 - 0.5 * lift;
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            number low = in1[(Index)i];
            number mid = in2[(Index)i];
            number high = in3[(Index)i];
            number lowCurved = fixnan(rnbo_pow((low > 1 ? 1 : (low < 0 ? 0 : low)), curveExp));
            number midCurved = fixnan(rnbo_pow((mid > 1 ? 1 : (mid < 0 ? 0 : mid)), curveExp));
            number highCurved = fixnan(rnbo_pow((high > 1 ? 1 : (high < 0 ? 0 : high)), curveExp));
            number lowLifted = floor + oneMinusFloor * lowCurved;
            number midLifted = floor + oneMinusFloor * midCurved;
            number highLifted = floor + oneMinusFloor * highCurved;
            out1[(Index)i] = (low + lift * (lowLifted - low) > 1 ? 1 : (low + lift * (lowLifted - low) < 0 ? 0 : low + lift * (lowLifted - low)));//#map:_###_obj_###_:18
            out2[(Index)i] = (mid + lift * (midLifted - mid) > 1 ? 1 : (mid + lift * (midLifted - mid) < 0 ? 0 : mid + lift * (midLifted - mid)));//#map:_###_obj_###_:19
            out3[(Index)i] = (high + lift * (highLifted - high) > 1 ? 1 : (high + lift * (highLifted - high) < 0 ? 0 : high + lift * (highLifted - high)));//#map:_###_obj_###_:20
        }
    }
    
    void codebox_tilde_03_perform(
        const Sample * in1,
        const Sample * in2,
        const Sample * in3,
        SampleValue * out1,
        SampleValue * out2,
        SampleValue * out3,
        SampleValue * out4,
        SampleValue * out5,
        SampleValue * out6,
        SampleValue * out7,
        SampleValue * out8,
        SampleValue * out9,
        Index n
    ) {
        number wildDuty = 0.1;
        Index i;
    
        for (i = 0; i < (Index)n; i++) {
            number lowWave = in1[(Index)i];
            number midWave = in2[(Index)i];
            number highWave = in3[(Index)i];
            number lowRate = 0.6 + lowWave * (3 - 0.6);
            number midRate = 2 + midWave * (9 - 2);
            number highRate = 5 + highWave * (18 - 5);
            number lowDepth = 0.2 + lowWave * (0.55 - 0.2);
            number midDepth = 0.35 + midWave * (0.85 - 0.35);
            number highDepth = 0.15 + highWave * (0.6 - 0.15);
            number lowDuty = (0.75 - lowWave * 0.3 > 0.95 ? 0.95 : (0.75 - lowWave * 0.3 < 0.05 ? 0.05 : 0.75 - lowWave * 0.3));
            number midDuty = (0.6 - midWave * 0.32 > 0.95 ? 0.95 : (0.6 - midWave * 0.32 < 0.05 ? 0.05 : 0.6 - midWave * 0.32));
            number highDuty = (0.35 - highWave * 0.2 > 0.95 ? 0.95 : (0.35 - highWave * 0.2 < 0.05 ? 0.05 : 0.35 - highWave * 0.2));
            out1[(Index)i] = lowRate;//#map:_###_obj_###_:22
            out2[(Index)i] = midRate;//#map:_###_obj_###_:23
            out3[(Index)i] = highRate;//#map:_###_obj_###_:24
            out4[(Index)i] = lowDepth;//#map:_###_obj_###_:26
            out5[(Index)i] = midDepth;//#map:_###_obj_###_:27
            out6[(Index)i] = highDepth;//#map:_###_obj_###_:28
            out7[(Index)i] = lowDuty;//#map:_###_obj_###_:30
            out8[(Index)i] = midDuty;//#map:_###_obj_###_:31
            out9[(Index)i] = highDuty;//#map:_###_obj_###_:32
        }
    }
    
    void stackprotect_perform(Index n) {
        RNBO_UNUSED(n);
        auto __stackprotect_count = this->stackprotect_count;
        __stackprotect_count = 0;
        this->stackprotect_count = __stackprotect_count;
    }
    
    template<typename BUFFERTYPE> void fftstream_tilde_01_fft_next(BUFFERTYPE& buffer, Int fftsize) {
        if (this->fftstream_tilde_01_fft_lastsize != fftsize) {
            for (Index i = 0; i < 32; i++) {
                if ((BinOpInt)((BinOpInt)1 << imod_nocast((UBinOpInt)i, 32)) == fftsize) {
                    this->fftstream_tilde_01_fft_levels = i;
                }
            }
    
            for (Index i = 0; i < fftsize; i++) {
                this->fftstream_tilde_01_fft_costab->push(rnbo_cos(6.28318530717958647692 * i / fftsize));
                this->fftstream_tilde_01_fft_sintab->push(rnbo_sin(6.28318530717958647692 * i / fftsize));
            }
    
            this->fftstream_tilde_01_fft_lastsize = fftsize;
        }
    
        if (this->fftstream_tilde_01_fft_levels != -1) {
            for (Index i = 0; i < fftsize; i++) {
                Index x = (Index)(i);
                Index j = 0;
    
                for (Index k = 0; k < this->fftstream_tilde_01_fft_levels; k++) {
                    j = (BinOpInt)((BinOpInt)((BinOpInt)j << imod_nocast((UBinOpInt)1, 32)) | (BinOpInt)((BinOpInt)x & (BinOpInt)1));
                    x = (BinOpInt)((BinOpInt)x >> imod_nocast((UBinOpInt)1, 32));
                }
    
                if (j > i) {
                    number temp = buffer[(Index)(2 * i)];
                    buffer[(Index)(2 * i)] = buffer[(Index)(2 * j)];
                    buffer[(Index)(2 * j)] = temp;
                    temp = buffer[(Index)(2 * i + 1)];
                    buffer[(Index)(2 * i + 1)] = buffer[(Index)(2 * j + 1)];
                    buffer[(Index)(2 * j + 1)] = temp;
                }
            }
    
            for (Index size = 2; size <= fftsize; size *= 2) {
                Index halfsize = (Index)(size / (number)2);
                Index tablestep = (Index)(fftsize / size);
    
                for (Index i = 0; i < fftsize; i += size) {
                    Index k = 0;
    
                    for (Index j = (Index)(i); j < i + halfsize; j++) {
                        Index l = (Index)(j + halfsize);
                        number real_l = buffer[(Index)(2 * l)];
                        number imag_l = buffer[(Index)(2 * l + 1)];
                        number tpre = real_l * this->fftstream_tilde_01_fft_costab[(Index)k] + imag_l * this->fftstream_tilde_01_fft_sintab[(Index)k];
                        number tpim = -real_l * this->fftstream_tilde_01_fft_sintab[(Index)k] + imag_l * this->fftstream_tilde_01_fft_costab[(Index)k];
                        number real_j = buffer[(Index)(2 * j)];
                        number imag_j = buffer[(Index)(2 * j + 1)];
                        buffer[(Index)(2 * l)] = real_j - tpre;
                        buffer[(Index)(2 * l + 1)] = imag_j - tpim;
                        buffer[(Index)(2 * j)] = real_j + tpre;
                        buffer[(Index)(2 * j + 1)] = imag_j + tpim;
                        k += tablestep;
                    }
                }
            }
        }
    }
    
    void fftstream_tilde_01_fft_reset() {
        this->fftstream_tilde_01_fft_lastsize = 0;
        this->fftstream_tilde_01_fft_costab = {};
        this->fftstream_tilde_01_fft_sintab = {};
        this->fftstream_tilde_01_fft_levels = -1;
    }
    
    void fftstream_tilde_01_dspsetup(bool force) {
        if ((bool)(this->fftstream_tilde_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        for (Int i = 0; i < 1024 * 2; i++) {
            this->fftstream_tilde_01_inWorkspace[(Index)i] = 0;
            this->fftstream_tilde_01_outWorkspace[(Index)i] = 0;
        }
    
        Int safeframesize = (Int)(1024);
    
        {
            safeframesize = nextpoweroftwo(1024);
        }
    
        Int framepos = (Int)(0 % safeframesize);
    
        if (framepos < 1024) {
            this->fftstream_tilde_01_datapos = framepos;
        } else {
            this->fftstream_tilde_01_datapos = 0;
        }
    
        this->fftstream_tilde_01_datapos = (this->audioProcessSampleCount + this->fftstream_tilde_01_datapos) % 1024;
        this->fftstream_tilde_01_setupDone = true;
    }
    
    void samplerate_01_onSampleRateChanged(number samplerate) {
        if (this->samplerate_01_samplerate != samplerate) {
            this->samplerate_01_samplerate_set(samplerate);
        }
    }
    
    void samplerate_01_dspsetup(bool force) {
        if ((bool)(this->samplerate_01_setupDone) && (bool)(!(bool)(force)))
            return;
    
        this->samplerate_01_onSampleRateChanged(this->sr);
        this->samplerate_01_setupDone = true;
    }
    
    bool stackprotect_check() {
        this->stackprotect_count++;
    
        if (this->stackprotect_count > 128) {
            console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
            return true;
        }
    
        return false;
    }
    
    Index getPatcherSerial() const {
        return 0;
    }
    
    void sendParameter(ParameterIndex index, bool ignoreValue) {
        this->getPatcher()->sendParameter(index + this->parameterOffset, ignoreValue);
    }
    
    void scheduleParamInit(ParameterIndex index, Index order) {
        this->getPatcher()->scheduleParamInit(index + this->parameterOffset, order);
    }
    
    void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
        RNBO_UNUSED(inProcess);
        RNBO_UNUSED(engine);
        this->_currentTime = time;
        auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));
    
        if (offset >= (SampleIndex)(this->vs))
            offset = (SampleIndex)(this->vs) - 1;
    
        if (offset < 0)
            offset = 0;
    
        this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
    }
    
    void assign_defaults()
    {
        fftstream_tilde_01_realIn = 0;
        fftstream_tilde_01_imagIn = 0;
        codebox_tilde_01_in1 = 0;
        codebox_tilde_01_in2 = 0;
        codebox_tilde_01_in3 = 0;
        codebox_tilde_01_in4 = 0;
        codebox_tilde_01_in5 = 0;
        codebox_tilde_01_in6 = 0;
        codebox_tilde_01_in7 = 0;
        codebox_tilde_02_in1 = 0;
        codebox_tilde_02_in2 = 0;
        codebox_tilde_02_in3 = 0;
        codebox_tilde_02_in4 = 0;
        codebox_tilde_03_in1 = 0;
        codebox_tilde_03_in2 = 0;
        codebox_tilde_03_in3 = 0;
        dspexpr_01_in1 = 0;
        dspexpr_01_in2 = 0;
        dspexpr_02_in1 = 0;
        dspexpr_02_in2 = 0;
        dspexpr_02_in3 = 1;
        slide_tilde_01_x = 0;
        slide_tilde_01_up = 400;
        slide_tilde_01_down = 2200;
        expr_01_in1 = 0;
        expr_01_in2 = 2;
        expr_01_in3 = 171;
        expr_01_out1 = 0;
        expr_02_in1 = 0;
        expr_02_out1 = 0;
        expr_03_in1 = 0;
        expr_03_in2 = 0;
        expr_03_out1 = 0;
        dspexpr_03_in1 = 0;
        dspexpr_03_in2 = 0;
        dspexpr_04_in1 = 0;
        dspexpr_04_in2 = 0;
        dspexpr_04_in3 = 1;
        slide_tilde_02_x = 0;
        slide_tilde_02_up = 220;
        slide_tilde_02_down = 1400;
        receive_01_output_number = 0;
        expr_04_in1 = 0;
        expr_04_in2 = 0.5;
        expr_04_out1 = 0;
        expr_05_in1 = 0;
        expr_05_in2 = 2;
        expr_05_in3 = 171;
        expr_05_out1 = 0;
        slide_tilde_03_x = 0;
        slide_tilde_03_up = 90;
        slide_tilde_03_down = 900;
        dspexpr_05_in1 = 0;
        dspexpr_05_in2 = 0;
        dspexpr_06_in1 = 0;
        dspexpr_06_in2 = 0;
        dspexpr_06_in3 = 1;
        expr_06_in1 = 0;
        expr_06_out1 = 0;
        expr_07_in1 = 0;
        expr_07_in2 = 0;
        expr_07_out1 = 0;
        receive_02_output_number = 0;
        expr_08_in1 = 0;
        expr_08_in2 = 1024;
        expr_08_out1 = 0;
        samplerate_01_samplerate = 0;
        receive_03_output_number = 0;
        receive_04_output_number = 0;
        _currentTime = 0;
        audioProcessSampleCount = 0;
        sampleOffsetIntoNextAudioBuffer = 0;
        zeroBuffer = nullptr;
        dummyBuffer = nullptr;
        signals[0] = nullptr;
        signals[1] = nullptr;
        signals[2] = nullptr;
        signals[3] = nullptr;
        signals[4] = nullptr;
        signals[5] = nullptr;
        didAllocateSignals = 0;
        vs = 0;
        maxvs = 0;
        sr = 44100;
        invsr = 0.000022675736961451248;
        fftstream_tilde_01_datapos = 0;
        fftstream_tilde_01_fft_lastsize = 0;
        fftstream_tilde_01_fft_levels = -1;
        fftstream_tilde_01_setupDone = false;
        codebox_tilde_01_prevBinIndex = 0;
        codebox_tilde_01_lowFrameSum = 0;
        codebox_tilde_01_midFrameSum = 0;
        codebox_tilde_01_highFrameSum = 0;
        codebox_tilde_01_heldLowShare = 0;
        codebox_tilde_01_heldMidShare = 0;
        codebox_tilde_01_heldHighShare = 0;
        codebox_tilde_01_heldLowMotion = 0;
        codebox_tilde_01_heldMidMotion = 0;
        codebox_tilde_01_heldHighMotion = 0;
        codebox_tilde_01_heldLowDrive = 0;
        codebox_tilde_01_heldMidDrive = 0;
        codebox_tilde_01_heldHighDrive = 0;
        codebox_tilde_01_frameSum = 0;
        codebox_tilde_01_weightedFrameSum = 0;
        codebox_tilde_01_weightedFrameSq = 0;
        codebox_tilde_01_adaptiveLowIndex = 17;
        codebox_tilde_01_adaptiveHighIndex = 42;
        codebox_tilde_01_heldCentroid = 0;
        codebox_tilde_01_heldSpread = 0;
        codebox_tilde_01_heldBaseLowIndex = 17;
        codebox_tilde_01_heldBaseHighIndex = 42;
        slide_tilde_01_prev = 0;
        slide_tilde_02_prev = 0;
        slide_tilde_03_prev = 0;
        samplerate_01_setupDone = false;
        stackprotect_count = 0;
        _voiceIndex = 0;
        _noteNumber = 0;
        isMuted = 1;
        parameterOffset = 0;
    }
    
        // data ref strings
        struct DataRefStrings {
        	static constexpr auto& name0 = "fftstream_tilde_01_win_bufobj";
        	static constexpr auto& file0 = "";
        	static constexpr auto& tag0 = "buffer~";
        	DataRefStrings* operator->() { return this; }
        	const DataRefStrings* operator->() const { return this; }
        };
    
        DataRefStrings dataRefStrings;
    
    // member variables
    
        number fftstream_tilde_01_realIn;
        number fftstream_tilde_01_imagIn;
        number codebox_tilde_01_in1;
        number codebox_tilde_01_in2;
        number codebox_tilde_01_in3;
        number codebox_tilde_01_in4;
        number codebox_tilde_01_in5;
        number codebox_tilde_01_in6;
        number codebox_tilde_01_in7;
        number codebox_tilde_02_in1;
        number codebox_tilde_02_in2;
        number codebox_tilde_02_in3;
        number codebox_tilde_02_in4;
        number codebox_tilde_03_in1;
        number codebox_tilde_03_in2;
        number codebox_tilde_03_in3;
        number dspexpr_01_in1;
        number dspexpr_01_in2;
        number dspexpr_02_in1;
        number dspexpr_02_in2;
        number dspexpr_02_in3;
        number slide_tilde_01_x;
        number slide_tilde_01_up;
        number slide_tilde_01_down;
        number expr_01_in1;
        number expr_01_in2;
        number expr_01_in3;
        number expr_01_out1;
        number expr_02_in1;
        number expr_02_out1;
        number expr_03_in1;
        number expr_03_in2;
        number expr_03_out1;
        number dspexpr_03_in1;
        number dspexpr_03_in2;
        number dspexpr_04_in1;
        number dspexpr_04_in2;
        number dspexpr_04_in3;
        number slide_tilde_02_x;
        number slide_tilde_02_up;
        number slide_tilde_02_down;
        number receive_01_output_number;
        list receive_01_output_list;
        number expr_04_in1;
        number expr_04_in2;
        number expr_04_out1;
        number expr_05_in1;
        number expr_05_in2;
        number expr_05_in3;
        number expr_05_out1;
        number slide_tilde_03_x;
        number slide_tilde_03_up;
        number slide_tilde_03_down;
        number dspexpr_05_in1;
        number dspexpr_05_in2;
        number dspexpr_06_in1;
        number dspexpr_06_in2;
        number dspexpr_06_in3;
        number expr_06_in1;
        number expr_06_out1;
        number expr_07_in1;
        number expr_07_in2;
        number expr_07_out1;
        number receive_02_output_number;
        list receive_02_output_list;
        number expr_08_in1;
        number expr_08_in2;
        number expr_08_out1;
        number samplerate_01_samplerate;
        number receive_03_output_number;
        list receive_03_output_list;
        number receive_04_output_number;
        list receive_04_output_list;
        MillisecondTime _currentTime;
        UInt64 audioProcessSampleCount;
        Index sampleOffsetIntoNextAudioBuffer;
        signal zeroBuffer;
        signal dummyBuffer;
        SampleValue * signals[6];
        bool didAllocateSignals;
        Index vs;
        Index maxvs;
        number sr;
        number invsr;
        SampleValue fftstream_tilde_01_inWorkspace[2048] = { };
        SampleValue fftstream_tilde_01_outWorkspace[2048] = { };
        SampleBufferRef fftstream_tilde_01_win_buf;
        SampleIndex fftstream_tilde_01_datapos;
        Int fftstream_tilde_01_fft_lastsize;
        list fftstream_tilde_01_fft_costab;
        list fftstream_tilde_01_fft_sintab;
        Int fftstream_tilde_01_fft_levels;
        bool fftstream_tilde_01_setupDone;
        number codebox_tilde_01_prevBinIndex;
        number codebox_tilde_01_lowFrameSum;
        number codebox_tilde_01_midFrameSum;
        number codebox_tilde_01_highFrameSum;
        number codebox_tilde_01_heldLowShare;
        number codebox_tilde_01_heldMidShare;
        number codebox_tilde_01_heldHighShare;
        number codebox_tilde_01_heldLowMotion;
        number codebox_tilde_01_heldMidMotion;
        number codebox_tilde_01_heldHighMotion;
        number codebox_tilde_01_heldLowDrive;
        number codebox_tilde_01_heldMidDrive;
        number codebox_tilde_01_heldHighDrive;
        number codebox_tilde_01_frameSum;
        number codebox_tilde_01_weightedFrameSum;
        number codebox_tilde_01_weightedFrameSq;
        number codebox_tilde_01_adaptiveLowIndex;
        number codebox_tilde_01_adaptiveHighIndex;
        number codebox_tilde_01_heldCentroid;
        number codebox_tilde_01_heldSpread;
        number codebox_tilde_01_heldBaseLowIndex;
        number codebox_tilde_01_heldBaseHighIndex;
        number slide_tilde_01_prev;
        number slide_tilde_02_prev;
        number slide_tilde_03_prev;
        bool samplerate_01_setupDone;
        number stackprotect_count;
        DataRef fftstream_tilde_01_win_bufobj;
        Index _voiceIndex;
        Int _noteNumber;
        Index isMuted;
        ParameterIndex parameterOffset;
        bool _isInitialized = false;
};

		
void advanceTime(EXTERNALENGINE*) {}
void advanceTime(INTERNALENGINE*) {
	_internalEngine.advanceTime(sampstoms(this->vs));
}

void processInternalEvents(MillisecondTime time) {
	_internalEngine.processEventsUntil(time);
}

void updateTime(MillisecondTime time, INTERNALENGINE*, bool inProcess = false) {
	if (time == TimeNow) time = getPatcherTime();
	processInternalEvents(inProcess ? time + sampsToMs(this->vs) : time);
	updateTime(time, (EXTERNALENGINE*)nullptr);
}

rnbomatic* operator->() {
    return this;
}
const rnbomatic* operator->() const {
    return this;
}
rnbomatic* getTopLevelPatcher() {
    return this;
}

void cancelClockEvents()
{
}

template<typename LISTTYPE = list> void listquicksort(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    if (l < h) {
        Int p = (Int)(this->listpartition(arr, sortindices, l, h, ascending));
        this->listquicksort(arr, sortindices, l, p - 1, ascending);
        this->listquicksort(arr, sortindices, p + 1, h, ascending);
    }
}

template<typename LISTTYPE = list> Int listpartition(LISTTYPE& arr, LISTTYPE& sortindices, Int l, Int h, bool ascending) {
    number x = arr[(Index)h];
    Int i = (Int)(l - 1);

    for (Int j = (Int)(l); j <= h - 1; j++) {
        bool asc = (bool)((bool)(ascending) && arr[(Index)j] <= x);
        bool desc = (bool)((bool)(!(bool)(ascending)) && arr[(Index)j] >= x);

        if ((bool)(asc) || (bool)(desc)) {
            i++;
            this->listswapelements(arr, i, j);
            this->listswapelements(sortindices, i, j);
        }
    }

    i++;
    this->listswapelements(arr, i, h);
    this->listswapelements(sortindices, i, h);
    return i;
}

template<typename LISTTYPE = list> void listswapelements(LISTTYPE& arr, Int a, Int b) {
    auto tmp = arr[(Index)a];
    arr[(Index)a] = arr[(Index)b];
    arr[(Index)b] = tmp;
}

number __wrapped_op_clamp(number in1, number in2, number in3) {
    return (in1 > in3 ? in3 : (in1 < in2 ? in2 : in1));
}

number minimum(number x, number y) {
    return (y < x ? y : x);
}

number maximum(number x, number y) {
    return (x < y ? y : x);
}

inline number safemod(number f, number m) {
    if (m != 0) {
        Int f_trunc = (Int)(trunc(f));
        Int m_trunc = (Int)(trunc(m));

        if (f == f_trunc && m == m_trunc) {
            f = f_trunc % m_trunc;
        } else {
            if (m < 0) {
                m = -m;
            }

            if (f >= m) {
                if (f >= m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f -= m;
                }
            } else if (f <= -m) {
                if (f <= -m * 2.0) {
                    number d = f / m;
                    Int i = (Int)(trunc(d));
                    d = d - i;
                    f = d * m;
                } else {
                    f += m;
                }
            }
        }
    } else {
        f = 0.0;
    }

    return f;
}

inline number safediv(number num, number denom) {
    return (denom == 0.0 ? 0.0 : num / denom);
}

number beattime() {
    return this->getTopLevelPatcher()->globaltransport_getBeatTime(this->_currentTime);
}

number lockedphase(number quantum) {
    auto phase = this->safemod(this->safediv(this->beattime(), quantum), 1);

    if (phase < 0)
        phase += 1.;

    return phase;
}

number mstosamps(MillisecondTime ms) {
    return ms * this->sr * 0.001;
}

MillisecondTime sampstoms(number samps) {
    return samps * 1000 / this->sr;
}

void param_01_value_set(number v) {
    v = this->param_01_value_constrain(v);
    this->param_01_value = v;
    this->sendParameter(0, false);

    if (this->param_01_value != this->param_01_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_01_lastValue = this->param_01_value;
    }

    this->send_02_input_number_set(v);
}

void param_02_value_set(number v) {
    v = this->param_02_value_constrain(v);
    this->param_02_value = v;
    this->sendParameter(1, false);

    if (this->param_02_value != this->param_02_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_02_lastValue = this->param_02_value;
    }

    this->expr_17_in1_set(v);
    this->send_01_input_number_set(v);
}

void param_03_value_set(number v) {
    v = this->param_03_value_constrain(v);
    this->param_03_value = v;
    this->sendParameter(2, false);

    if (this->param_03_value != this->param_03_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_03_lastValue = this->param_03_value;
    }

    this->boolnum_01_val_set(v);
}

void param_04_value_set(number v) {
    v = this->param_04_value_constrain(v);
    this->param_04_value = v;
    this->sendParameter(3, false);

    if (this->param_04_value != this->param_04_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_04_lastValue = this->param_04_value;
    }

    this->send_04_input_number_set(v);
}

void param_05_value_set(number v) {
    v = this->param_05_value_constrain(v);
    this->param_05_value = v;
    this->sendParameter(4, false);

    if (this->param_05_value != this->param_05_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_05_lastValue = this->param_05_value;
    }

    this->boolnum_02_val_set(v);
}

void param_06_value_set(number v) {
    v = this->param_06_value_constrain(v);
    this->param_06_value = v;
    this->sendParameter(5, false);

    if (this->param_06_value != this->param_06_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_06_lastValue = this->param_06_value;
    }

    this->send_07_input_number_set(v);
}

void param_07_value_set(number v) {
    v = this->param_07_value_constrain(v);
    this->param_07_value = v;
    this->sendParameter(6, false);

    if (this->param_07_value != this->param_07_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_07_lastValue = this->param_07_value;
    }

    this->expr_21_in1_set(v);
    this->send_08_input_number_set(v);
}

void param_08_value_set(number v) {
    v = this->param_08_value_constrain(v);
    this->param_08_value = v;
    this->sendParameter(7, false);

    if (this->param_08_value != this->param_08_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_08_lastValue = this->param_08_value;
    }

    this->send_09_input_number_set(v);
}

void param_09_value_set(number v) {
    v = this->param_09_value_constrain(v);
    this->param_09_value = v;
    this->sendParameter(8, false);

    if (this->param_09_value != this->param_09_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_09_lastValue = this->param_09_value;
    }

    this->send_10_input_number_set(v);
}

void param_10_value_set(number v) {
    v = this->param_10_value_constrain(v);
    this->param_10_value = v;
    this->sendParameter(9, false);

    if (this->param_10_value != this->param_10_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_10_lastValue = this->param_10_value;
    }

    this->send_11_input_number_set(v);
}

void param_11_value_set(number v) {
    v = this->param_11_value_constrain(v);
    this->param_11_value = v;
    this->sendParameter(10, false);

    if (this->param_11_value != this->param_11_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_11_lastValue = this->param_11_value;
    }

    this->boolnum_03_val_set(v);
}

void param_12_value_set(number v) {
    v = this->param_12_value_constrain(v);
    this->param_12_value = v;
    this->sendParameter(11, false);

    if (this->param_12_value != this->param_12_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_12_lastValue = this->param_12_value;
    }

    this->expr_23_in1_set(v);
    this->codebox_tilde_05_in13_set(v);
}

void param_13_value_set(number v) {
    v = this->param_13_value_constrain(v);
    this->param_13_value = v;
    this->sendParameter(12, false);

    if (this->param_13_value != this->param_13_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_13_lastValue = this->param_13_value;
    }

    this->expr_25_in1_set(v);
    this->codebox_tilde_05_in14_set(v);
}

void param_14_value_set(number v) {
    v = this->param_14_value_constrain(v);
    this->param_14_value = v;
    this->sendParameter(13, false);

    if (this->param_14_value != this->param_14_lastValue) {
        {
            this->getEngine()->presetTouched();
        }

        this->param_14_lastValue = this->param_14_value;
    }

    this->send_14_input_number_set(v);
}

MillisecondTime getPatcherTime() const {
    return this->_currentTime;
}

void numberobj_01_valin_set(number v) {
    this->numberobj_01_value_set(v);
}

void numberobj_01_format_set(number v) {
    this->numberobj_01_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_02_valin_set(number v) {
    this->numberobj_02_value_set(v);
}

void numberobj_02_format_set(number v) {
    this->numberobj_02_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void numberobj_03_valin_set(number v) {
    this->numberobj_03_value_set(v);
}

void numberobj_03_format_set(number v) {
    this->numberobj_03_currentFormat = trunc((v > 6 ? 6 : (v < 0 ? 0 : v)));
}

void deallocateSignals() {
    Index i;

    for (i = 0; i < 27; i++) {
        this->signals[i] = freeSignal(this->signals[i]);
    }

    this->phasor_01_sigbuf = freeSignal(this->phasor_01_sigbuf);
    this->phasor_02_sigbuf = freeSignal(this->phasor_02_sigbuf);
    this->phasor_03_sigbuf = freeSignal(this->phasor_03_sigbuf);
    this->globaltransport_tempo = freeSignal(this->globaltransport_tempo);
    this->globaltransport_state = freeSignal(this->globaltransport_state);
    this->zeroBuffer = freeSignal(this->zeroBuffer);
    this->dummyBuffer = freeSignal(this->dummyBuffer);
}

Index getMaxBlockSize() const {
    return this->maxvs;
}

number getSampleRate() const {
    return this->sr;
}

bool hasFixedVectorSize() const {
    return false;
}

void setProbingTarget(MessageTag ) {}

void fillDataRef(DataRefIndex , DataRef& ) {}

void allocateDataRefs() {
    this->p_01->allocateDataRefs();
}

void initializeObjects() {
    this->numberobj_01_init();
    this->numberobj_02_init();
    this->numberobj_03_init();
    this->p_01->initializeObjects();
}

Index getIsMuted()  {
    return this->isMuted;
}

void setIsMuted(Index v)  {
    this->isMuted = v;
}

void onSampleRateChanged(double ) {}

void extractState(PatcherStateInterface& ) {}

void applyState() {

    this->p_01->setEngineAndPatcher(this->getEngine(), this);
    this->p_01->initialize();
    this->p_01->setParameterOffset(this->getParameterOffset(this->p_01));
}

ParameterIndex getParameterOffset(BaseInterface& subpatcher) const {
    if (addressOf(subpatcher) == addressOf(this->p_01))
        return 14;

    return 0;
}

void processClockEvent(MillisecondTime , ClockId , bool , ParameterValue ) {}

void processOutletAtCurrentTime(EngineLink* , OutletIndex , ParameterValue ) {}

void processOutletEvent(
    EngineLink* sender,
    OutletIndex index,
    ParameterValue value,
    MillisecondTime time
) {
    this->updateTime(time, (ENGINE*)nullptr);
    this->processOutletAtCurrentTime(sender, index, value);
}

void sendOutlet(OutletIndex index, ParameterValue value) {
    this->getEngine()->sendOutlet(this, index, value);
}

void startup() {
    this->updateTime(this->getEngine()->getCurrentTime(), (ENGINE*)nullptr);
    this->p_01->startup();

    {
        this->scheduleParamInit(0, 0);
    }

    {
        this->scheduleParamInit(1, 0);
    }

    {
        this->scheduleParamInit(2, 0);
    }

    {
        this->scheduleParamInit(3, 0);
    }

    {
        this->scheduleParamInit(4, 0);
    }

    {
        this->scheduleParamInit(5, 0);
    }

    {
        this->scheduleParamInit(6, 0);
    }

    {
        this->scheduleParamInit(7, 0);
    }

    {
        this->scheduleParamInit(8, 0);
    }

    {
        this->scheduleParamInit(9, 0);
    }

    {
        this->scheduleParamInit(10, 0);
    }

    {
        this->scheduleParamInit(11, 0);
    }

    {
        this->scheduleParamInit(12, 0);
    }

    {
        this->scheduleParamInit(13, 0);
    }

    this->processParamInitEvents();
}

number param_01_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void dspexpr_43_in2_set(number v) {
    this->dspexpr_43_in2 = v;
}

void dspexpr_40_in2_set(number v) {
    this->dspexpr_40_in2 = v;
}

void dspexpr_37_in2_set(number v) {
    this->dspexpr_37_in2 = v;
}

void dspexpr_32_in2_set(number v) {
    this->dspexpr_32_in2 = v;
}

void dspexpr_27_in2_set(number v) {
    this->dspexpr_27_in2 = v;
}

void dspexpr_26_in2_set(number v) {
    this->dspexpr_26_in2 = v;
}

void receive_13_output_number_set(number v) {
    this->receive_13_output_number = v;
    this->dspexpr_43_in2_set(v);
    this->dspexpr_40_in2_set(v);
    this->dspexpr_37_in2_set(v);
    this->dspexpr_32_in2_set(v);
    this->dspexpr_27_in2_set(v);
    this->dspexpr_26_in2_set(v);
}

void send_02_input_number_set(number v) {
    this->send_02_input_number = v;
    this->receive_13_output_number_set(v);
}

number param_02_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void dspexpr_17_in2_set(number v) {
    this->dspexpr_17_in2 = v;
}

void dspexpr_14_in2_set(number v) {
    this->dspexpr_14_in2 = v;
}

void dspexpr_12_in2_set(number v) {
    this->dspexpr_12_in2 = v;
}

void receive_06_output_number_set(number v) {
    this->receive_06_output_number = v;
    this->dspexpr_17_in2_set(v);
    this->dspexpr_14_in2_set(v);
    this->dspexpr_12_in2_set(v);
}

void send_06_input_number_set(number v) {
    this->send_06_input_number = v;
    this->receive_06_output_number_set(v);
}

void expr_18_out1_set(number v) {
    this->expr_18_out1 = v;
    this->send_06_input_number_set(this->expr_18_out1);
}

void expr_18_in1_set(number in1) {
    this->expr_18_in1 = in1;
    this->expr_18_out1_set(rnbo_pow(2, this->expr_18_in1));//#map:exp2_obj-128:1
}

void expr_16_out1_set(number v) {
    this->expr_16_out1 = v;
    this->expr_18_in1_set(this->expr_16_out1);
}

void expr_16_in1_set(number in1) {
    this->expr_16_in1 = in1;
    this->expr_16_out1_set(this->expr_16_in1 - this->expr_16_in2);//#map:-_obj-130:1
}

void expr_17_out1_set(number v) {
    this->expr_17_out1 = v;
    this->expr_16_in1_set(this->expr_17_out1);
}

void expr_17_in1_set(number in1) {
    this->expr_17_in1 = in1;
    this->expr_17_out1_set(this->expr_17_in1 * this->expr_17_in2);//#map:*_obj-129:1
}

void codebox_tilde_04_in1_set(number v) {
    this->codebox_tilde_04_in1 = v;
}

void receive_07_output_number_set(number v) {
    this->receive_07_output_number = v;
    this->codebox_tilde_04_in1_set(v);
}

void send_01_input_number_set(number v) {
    this->send_01_input_number = v;
    this->receive_07_output_number_set(v);
}

number param_03_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

number boolnum_01_val_constrain(number v) const {
    return v != 0;
}

number boolnum_01_out1_constrain(number v) const {
    return v != 0;
}

void send_03_input_number_set(number v) {
    this->send_03_input_number = v;
}

void boolnum_01_out1_set(number v) {
    v = this->boolnum_01_out1_constrain(v);
    this->send_03_input_number_set(v);
}

void boolnum_01_val_set(number val) {
    val = this->boolnum_01_val_constrain(val);
    this->boolnum_01_val = val;

    {
        this->boolnum_01_out1_set(!(bool)(!(bool)(val)));
        return;
    }
}

number param_04_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void p_01_target_sensitivity_number_set(number v) {
    this->p_01->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_01->receive_01_output_number_set(v);
}

void send_04_input_number_set(number v) {
    this->send_04_input_number = v;
    this->p_01_target_sensitivity_number_set(v);
}

number param_05_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

number boolnum_02_val_constrain(number v) const {
    return v != 0;
}

number boolnum_02_out1_constrain(number v) const {
    return v != 0;
}

void selector_03_onoff_set(number v) {
    this->selector_03_onoff = v;
}

void selector_02_onoff_set(number v) {
    this->selector_02_onoff = v;
}

void selector_01_onoff_set(number v) {
    this->selector_01_onoff = v;
}

void receive_09_output_number_set(number v) {
    this->receive_09_output_number = v;
    this->selector_03_onoff_set(v);
    this->selector_02_onoff_set(v);
    this->selector_01_onoff_set(v);
}

void send_05_input_number_set(number v) {
    this->send_05_input_number = v;
    this->receive_09_output_number_set(v);
}

void expr_15_out1_set(number v) {
    this->expr_15_out1 = v;
    this->send_05_input_number_set(this->expr_15_out1);
}

void expr_15_in1_set(number in1) {
    this->expr_15_in1 = in1;
    this->expr_15_out1_set(this->expr_15_in1 + this->expr_15_in2);//#map:+_obj-402:1
}

void boolnum_02_out1_set(number v) {
    v = this->boolnum_02_out1_constrain(v);
    this->expr_15_in1_set(v);
}

void boolnum_02_val_set(number val) {
    val = this->boolnum_02_val_constrain(val);
    this->boolnum_02_val = val;

    {
        this->boolnum_02_out1_set(!(bool)(!(bool)(val)));
        return;
    }
}

number param_06_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void p_01_target_lift_number_set(number v) {
    this->p_01->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_01->receive_03_output_number_set(v);
}

void send_07_input_number_set(number v) {
    this->send_07_input_number = v;
    this->p_01_target_lift_number_set(v);
}

number param_07_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void gen_05_in5_set(number v) {
    this->gen_05_in5 = v;
}

void gen_06_in5_set(number v) {
    this->gen_06_in5 = v;
}

void gen_04_in5_set(number v) {
    this->gen_04_in5 = v;
}

void gen_02_in5_set(number v) {
    this->gen_02_in5 = v;
}

void gen_03_in5_set(number v) {
    this->gen_03_in5 = v;
}

void gen_01_in5_set(number v) {
    this->gen_01_in5 = v;
}

void receive_11_output_number_set(number v) {
    this->receive_11_output_number = v;
    this->gen_05_in5_set(v);
    this->gen_06_in5_set(v);
    this->gen_04_in5_set(v);
    this->gen_02_in5_set(v);
    this->gen_03_in5_set(v);
    this->gen_01_in5_set(v);
}

void send_12_input_number_set(number v) {
    this->send_12_input_number = v;
    this->receive_11_output_number_set(v);
}

void expr_20_out1_set(number v) {
    this->expr_20_out1 = v;
    this->send_12_input_number_set(this->expr_20_out1);
}

void expr_20_in1_set(number in1) {
    this->expr_20_in1 = in1;
    this->expr_20_out1_set(this->expr_20_in2 - this->expr_20_in1);//#map:!-_obj-192:1
}

void expr_21_out1_set(number v) {
    this->expr_21_out1 = v;
    this->expr_20_in1_set(this->expr_21_out1);
}

void expr_21_in1_set(number in1) {
    this->expr_21_in1 = in1;
    this->expr_21_out1_set(this->expr_21_in1 * this->expr_21_in2);//#map:*_obj-191:1
}

void dspexpr_42_in2_set(number v) {
    this->dspexpr_42_in2 = v;
}

void dspexpr_31_in2_set(number v) {
    this->dspexpr_31_in2 = v;
}

void expr_14_out1_set(number v) {
    this->expr_14_out1 = v;
    this->dspexpr_42_in2_set(this->expr_14_out1);
    this->dspexpr_31_in2_set(this->expr_14_out1);
}

void expr_14_in1_set(number in1) {
    this->expr_14_in1 = in1;
    this->expr_14_out1_set(this->expr_14_in1 * this->expr_14_in2);//#map:*_obj-165:1
}

void dspexpr_39_in2_set(number v) {
    this->dspexpr_39_in2 = v;
}

void dspexpr_29_in2_set(number v) {
    this->dspexpr_29_in2 = v;
}

void expr_13_out1_set(number v) {
    this->expr_13_out1 = v;
    this->dspexpr_39_in2_set(this->expr_13_out1);
    this->dspexpr_29_in2_set(this->expr_13_out1);
}

void expr_13_in1_set(number in1) {
    this->expr_13_in1 = in1;
    this->expr_13_out1_set(this->expr_13_in1 * this->expr_13_in2);//#map:*_obj-164:1
}

void dspexpr_36_in2_set(number v) {
    this->dspexpr_36_in2 = v;
}

void dspexpr_25_in2_set(number v) {
    this->dspexpr_25_in2 = v;
}

void expr_12_out1_set(number v) {
    this->expr_12_out1 = v;
    this->dspexpr_36_in2_set(this->expr_12_out1);
    this->dspexpr_25_in2_set(this->expr_12_out1);
}

void expr_12_in1_set(number in1) {
    this->expr_12_in1 = in1;
    this->expr_12_out1_set(this->expr_12_in1 * this->expr_12_in2);//#map:*_obj-163:1
}

void receive_12_output_number_set(number v) {
    this->receive_12_output_number = v;
    this->expr_14_in1_set(v);
    this->expr_13_in1_set(v);
    this->expr_12_in1_set(v);
}

void dspexpr_49_in2_set(number v) {
    this->dspexpr_49_in2 = v;
}

void expr_24_out1_set(number v) {
    this->expr_24_out1 = v;
    this->dspexpr_49_in2_set(this->expr_24_out1);
}

void expr_24_in1_set(number in1) {
    this->expr_24_in1 = in1;
    this->expr_24_out1_set(this->expr_24_in1 * this->expr_24_in2);//#map:*_obj-159:1
}

void dspexpr_47_in2_set(number v) {
    this->dspexpr_47_in2 = v;
}

void expr_22_out1_set(number v) {
    this->expr_22_out1 = v;
    this->dspexpr_47_in2_set(this->expr_22_out1);
}

void expr_22_in1_set(number in1) {
    this->expr_22_in1 = in1;
    this->expr_22_out1_set(this->expr_22_in1 * this->expr_22_in2);//#map:*_obj-154:1
}

void dspexpr_45_in2_set(number v) {
    this->dspexpr_45_in2 = v;
}

void expr_19_out1_set(number v) {
    this->expr_19_out1 = v;
    this->dspexpr_45_in2_set(this->expr_19_out1);
}

void expr_19_in1_set(number in1) {
    this->expr_19_in1 = in1;
    this->expr_19_out1_set(this->expr_19_in1 * this->expr_19_in2);//#map:*_obj-140:1
}

void receive_14_output_number_set(number v) {
    this->receive_14_output_number = v;
    this->expr_24_in1_set(v);
    this->expr_22_in1_set(v);
    this->expr_19_in1_set(v);
}

void send_08_input_number_set(number v) {
    this->send_08_input_number = v;
    this->receive_12_output_number_set(v);
    this->receive_14_output_number_set(v);
}

number param_08_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void codebox_tilde_05_in1_set(number v) {
    this->codebox_tilde_05_in1 = v;
}

void dspexpr_09_in2_set(number v) {
    this->dspexpr_09_in2 = v;
}

void numberobj_01_output_set(number ) {}

void numberobj_01_value_set(number v) {
    this->numberobj_01_value_setter(v);
    v = this->numberobj_01_value;
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_01_output_set(localvalue);
}

void dspexpr_07_in2_set(number v) {
    this->dspexpr_07_in2 = v;
}

void expr_09_out1_set(number v) {
    this->expr_09_out1 = v;
    this->codebox_tilde_05_in1_set(this->expr_09_out1);
    this->dspexpr_09_in2_set(this->expr_09_out1);
    this->numberobj_01_value_set(this->expr_09_out1);
    this->dspexpr_07_in2_set(this->expr_09_out1);
}

void expr_09_in1_set(number in1) {
    this->expr_09_in1 = in1;
    this->expr_09_out1_set(this->expr_09_in1 * this->expr_09_in2);//#map:*_obj-312:1
}

void receive_05_output_number_set(number v) {
    this->receive_05_output_number = v;
    this->expr_09_in1_set(v);
}

void send_09_input_number_set(number v) {
    this->send_09_input_number = v;
    this->receive_05_output_number_set(v);
}

number param_09_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void codebox_tilde_05_in2_set(number v) {
    this->codebox_tilde_05_in2 = v;
}

void numberobj_02_output_set(number ) {}

void numberobj_02_value_set(number v) {
    this->numberobj_02_value_setter(v);
    v = this->numberobj_02_value;
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_02_output_set(localvalue);
}

void dspexpr_16_in2_set(number v) {
    this->dspexpr_16_in2 = v;
}

void dspexpr_11_in2_set(number v) {
    this->dspexpr_11_in2 = v;
}

void expr_10_out1_set(number v) {
    this->expr_10_out1 = v;
    this->codebox_tilde_05_in2_set(this->expr_10_out1);
    this->numberobj_02_value_set(this->expr_10_out1);
    this->dspexpr_16_in2_set(this->expr_10_out1);
    this->dspexpr_11_in2_set(this->expr_10_out1);
}

void expr_10_in1_set(number in1) {
    this->expr_10_in1 = in1;
    this->expr_10_out1_set(this->expr_10_in1 * this->expr_10_in2);//#map:*_obj-313:1
}

void receive_08_output_number_set(number v) {
    this->receive_08_output_number = v;
    this->expr_10_in1_set(v);
}

void send_10_input_number_set(number v) {
    this->send_10_input_number = v;
    this->receive_08_output_number_set(v);
}

number param_10_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));
    return v;
}

void codebox_tilde_05_in3_set(number v) {
    this->codebox_tilde_05_in3 = v;
}

void dspexpr_23_in2_set(number v) {
    this->dspexpr_23_in2 = v;
}

void numberobj_03_output_set(number ) {}

void numberobj_03_value_set(number v) {
    this->numberobj_03_value_setter(v);
    v = this->numberobj_03_value;
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_03_output_set(localvalue);
}

void dspexpr_20_in2_set(number v) {
    this->dspexpr_20_in2 = v;
}

void expr_11_out1_set(number v) {
    this->expr_11_out1 = v;
    this->codebox_tilde_05_in3_set(this->expr_11_out1);
    this->dspexpr_23_in2_set(this->expr_11_out1);
    this->numberobj_03_value_set(this->expr_11_out1);
    this->dspexpr_20_in2_set(this->expr_11_out1);
}

void expr_11_in1_set(number in1) {
    this->expr_11_in1 = in1;
    this->expr_11_out1_set(this->expr_11_in1 * this->expr_11_in2);//#map:*_obj-314:1
}

void receive_10_output_number_set(number v) {
    this->receive_10_output_number = v;
    this->expr_11_in1_set(v);
}

void send_11_input_number_set(number v) {
    this->send_11_input_number = v;
    this->receive_10_output_number_set(v);
}

number param_11_value_constrain(number v) const {
    v = (v > 1 ? 1 : (v < 0 ? 0 : v));

    {
        number oneStep = (number)1 / (number)1;
        number oneStepInv = (oneStep != 0 ? (number)1 / oneStep : 0);
        number numberOfSteps = rnbo_fround((v - 0) * oneStepInv * 1 / (number)1) * 1;
        v = numberOfSteps * oneStep + 0;
    }

    return v;
}

number boolnum_03_val_constrain(number v) const {
    return v != 0;
}

number boolnum_03_out1_constrain(number v) const {
    return v != 0;
}

void p_01_target_adaptive_mode_number_set(number v) {
    this->p_01->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_01->receive_02_output_number_set(v);
}

void send_13_input_number_set(number v) {
    this->send_13_input_number = v;
    this->p_01_target_adaptive_mode_number_set(v);
}

void boolnum_03_out1_set(number v) {
    v = this->boolnum_03_out1_constrain(v);
    this->send_13_input_number_set(v);
}

void boolnum_03_val_set(number val) {
    val = this->boolnum_03_val_constrain(val);
    this->boolnum_03_val = val;

    {
        this->boolnum_03_out1_set(!(bool)(!(bool)(val)));
        return;
    }
}

number param_12_value_constrain(number v) const {
    v = (v > 4000 ? 4000 : (v < 0 ? 0 : v));
    return v;
}

void codebox_tilde_06_in1_set(number v) {
    this->codebox_tilde_06_in1 = v;
}

void expr_23_out1_set(number v) {
    this->expr_23_out1 = v;
    this->codebox_tilde_06_in1_set(this->expr_23_out1);
}

void expr_23_in1_set(number in1) {
    this->expr_23_in1 = in1;

    this->expr_23_out1_set(
        (this->expr_23_in1 > this->expr_23_in3 ? this->expr_23_in3 : (this->expr_23_in1 < this->expr_23_in2 ? this->expr_23_in2 : this->expr_23_in1))
    );//#map:clamp_obj-148:1
}

void codebox_tilde_05_in13_set(number v) {
    this->codebox_tilde_05_in13 = v;
}

number param_13_value_constrain(number v) const {
    v = (v > 8000 ? 8000 : (v < 0 ? 0 : v));
    return v;
}

void codebox_tilde_06_in2_set(number v) {
    this->codebox_tilde_06_in2 = v;
}

void expr_25_out1_set(number v) {
    this->expr_25_out1 = v;
    this->codebox_tilde_06_in2_set(this->expr_25_out1);
}

void expr_25_in1_set(number in1) {
    this->expr_25_in1 = in1;

    this->expr_25_out1_set(
        (this->expr_25_in1 > this->expr_25_in3 ? this->expr_25_in3 : (this->expr_25_in1 < this->expr_25_in2 ? this->expr_25_in2 : this->expr_25_in1))
    );//#map:clamp_obj-149:1
}

void codebox_tilde_05_in14_set(number v) {
    this->codebox_tilde_05_in14 = v;
}

number param_14_value_constrain(number v) const {
    v = (v > 0.9 ? 0.9 : (v < 0.1 ? 0.1 : v));
    return v;
}

void p_01_target_adaptive_alpha_number_set(number v) {
    this->p_01->updateTime(this->_currentTime, (ENGINE*)nullptr);
    this->p_01->receive_04_output_number_set(v);
}

void send_14_input_number_set(number v) {
    this->send_14_input_number = v;
    this->p_01_target_adaptive_alpha_number_set(v);
}

void signalsend_01_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void codebox_tilde_04_perform(
    number in1,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    Index n
) {
    number speed = (in1 > 1 ? 1 : (in1 < 0 ? 0 : in1));
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number step = this->__wrapped_op_clamp(rnbo_fround(speed * 5 * 1 / (number)1) * 1, 0, 5);
        number baseBeats = 2;

        if (step == 1) {
            baseBeats = 1;//#map:_###_obj_###_:5
        } else if (step == 2) {
            baseBeats = 0.5;//#map:_###_obj_###_:7
        } else if (step == 3) {
            baseBeats = 0.25;//#map:_###_obj_###_:9
        } else if (step == 4) {
            baseBeats = 0.125;//#map:_###_obj_###_:11
        } else if (step >= 5) {
            baseBeats = 0.0625;//#map:_###_obj_###_:13
        }//#map:_###_obj_###_:12//#map:_###_obj_###_:10//#map:_###_obj_###_:8//#map:_###_obj_###_:6//#map:_###_obj_###_:4

        auto lowBeats = this->minimum(baseBeats * 2, 4);
        number midBeats = baseBeats;
        auto highBeats = this->maximum(baseBeats * 0.5, 0.03125);
        out1[(Index)i] = this->lockedphase(lowBeats);//#map:_###_obj_###_:18
        out2[(Index)i] = this->lockedphase(midBeats);//#map:_###_obj_###_:19
        out3[(Index)i] = this->lockedphase(highBeats);//#map:_###_obj_###_:20
    }
}

void signalsend_05_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void codebox_tilde_06_perform(number in1, number in2, SampleValue * out1, SampleValue * out2, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number rawLowSplit = (in1 > 4000 ? 4000 : (in1 < 0 ? 0 : in1));
        number rawHighSplit = (in2 > 8000 ? 8000 : (in2 < 0 ? 0 : in2));
        number lowActive = rawLowSplit > 0.001;
        number highActive = rawHighSplit > 0.001;
        number lowSplit = 800;
        number highSplit = 2000;

        if ((bool)(lowActive) && (bool)(highActive)) {
            lowSplit = rawLowSplit;//#map:_###_obj_###_:11
            highSplit = rawHighSplit;//#map:_###_obj_###_:12

            if (lowSplit > highSplit) {
                number prevLowSplit = lowSplit;
                lowSplit = highSplit;//#map:_###_obj_###_:16
                highSplit = prevLowSplit;//#map:_###_obj_###_:17
            }//#map:_###_obj_###_:14

            if (highSplit < lowSplit + 300) {
                highSplit = lowSplit + 300;//#map:_###_obj_###_:21
            }//#map:_###_obj_###_:20

            lowSplit = (lowSplit > 4000 ? 4000 : (lowSplit < 40 ? 40 : lowSplit));//#map:_###_obj_###_:24
            highSplit = (highSplit > 8000 ? 8000 : (highSplit < 340 ? 340 : highSplit));//#map:_###_obj_###_:25

            if (lowSplit > highSplit - 300) {
                lowSplit = (highSplit - 300 > 4000 ? 4000 : (highSplit - 300 < 40 ? 40 : highSplit - 300));//#map:_###_obj_###_:28
            }//#map:_###_obj_###_:27
        } else if ((bool)(lowActive)) {
            lowSplit = (rawLowSplit > 4000 ? 4000 : (rawLowSplit < 40 ? 40 : rawLowSplit));//#map:_###_obj_###_:31
            highSplit = this->__wrapped_op_clamp(this->maximum(lowSplit + 300, 2000), 340, 8000);//#map:_###_obj_###_:32
        } else if ((bool)(highActive)) {
            highSplit = this->__wrapped_op_clamp(this->maximum(rawHighSplit, 340), 340, 8000);//#map:_###_obj_###_:34
            lowSplit = this->__wrapped_op_clamp(this->minimum(highSplit - 300, 800), 40, 4000);//#map:_###_obj_###_:35
        }//#map:_###_obj_###_:33//#map:_###_obj_###_:30//#map:_###_obj_###_:10

        out1[(Index)i] = lowSplit;//#map:_###_obj_###_:38
        out2[(Index)i] = highSplit;//#map:_###_obj_###_:39
    }
}

void signalsend_10_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_02_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void cross_tilde_03_perform(
    const Sample * x,
    const Sample * freq,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    auto __cross_tilde_03_y2H = this->cross_tilde_03_y2H;
    auto __cross_tilde_03_y1H = this->cross_tilde_03_y1H;
    auto __cross_tilde_03_y0H = this->cross_tilde_03_y0H;
    auto __cross_tilde_03_y2L = this->cross_tilde_03_y2L;
    auto __cross_tilde_03_y1L = this->cross_tilde_03_y1L;
    auto __cross_tilde_03_y0L = this->cross_tilde_03_y0L;
    auto __cross_tilde_03_x2 = this->cross_tilde_03_x2;
    auto __cross_tilde_03_x1 = this->cross_tilde_03_x1;
    auto __cross_tilde_03_x3 = this->cross_tilde_03_x3;
    auto __cross_tilde_03_x0 = this->cross_tilde_03_x0;
    auto __cross_tilde_03_oneOverA1 = this->cross_tilde_03_oneOverA1;
    auto __cross_tilde_03_oneOverA0 = this->cross_tilde_03_oneOverA0;
    auto __cross_tilde_03_b2 = this->cross_tilde_03_b2;
    auto __cross_tilde_03_b1 = this->cross_tilde_03_b1;
    auto __cross_tilde_03_b0 = this->cross_tilde_03_b0;
    auto __cross_tilde_03_needsUpdate = this->cross_tilde_03_needsUpdate;
    auto __cross_tilde_03__freq = this->cross_tilde_03__freq;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (__cross_tilde_03__freq != freq[(Index)i] || (bool)(__cross_tilde_03_needsUpdate)) {
            __cross_tilde_03__freq = freq[(Index)i];
            array<number, 5> coeffs = this->cross_tilde_03_calculateCoefficients(__cross_tilde_03__freq);
            __cross_tilde_03_b0 = coeffs[0];
            __cross_tilde_03_b1 = coeffs[1];
            __cross_tilde_03_b2 = coeffs[2];
            __cross_tilde_03_oneOverA0 = coeffs[3];
            __cross_tilde_03_oneOverA1 = coeffs[4];
            __cross_tilde_03_needsUpdate = false;
        }

        __cross_tilde_03_x0 = x[(Index)i];
        number lowPass = (number)((__cross_tilde_03_x0 + __cross_tilde_03_x3 + 3.0 * (__cross_tilde_03_x1 + __cross_tilde_03_x2)) * __cross_tilde_03_oneOverA0 + (__cross_tilde_03_y0L * __cross_tilde_03_b0 + __cross_tilde_03_y1L * __cross_tilde_03_b1 + __cross_tilde_03_y2L * __cross_tilde_03_b2));
        number highPass = (number)((__cross_tilde_03_x3 - __cross_tilde_03_x0 + 3.0 * (__cross_tilde_03_x1 - __cross_tilde_03_x2)) * __cross_tilde_03_oneOverA1 + (__cross_tilde_03_y0H * __cross_tilde_03_b0 + __cross_tilde_03_y1H * __cross_tilde_03_b1 + __cross_tilde_03_y2H * __cross_tilde_03_b2));
        __cross_tilde_03_x3 = __cross_tilde_03_x2;
        __cross_tilde_03_x2 = __cross_tilde_03_x1;
        __cross_tilde_03_x1 = __cross_tilde_03_x0;
        __cross_tilde_03_y2L = __cross_tilde_03_y1L;
        __cross_tilde_03_y1L = __cross_tilde_03_y0L;
        __cross_tilde_03_y0L = fixdenorm(lowPass);
        __cross_tilde_03_y2H = __cross_tilde_03_y1H;
        __cross_tilde_03_y1H = __cross_tilde_03_y0H;
        __cross_tilde_03_y0H = fixdenorm(highPass);
        out1[(Index)i] = lowPass;
        out2[(Index)i] = highPass;
    }

    this->cross_tilde_03__freq = __cross_tilde_03__freq;
    this->cross_tilde_03_needsUpdate = __cross_tilde_03_needsUpdate;
    this->cross_tilde_03_b0 = __cross_tilde_03_b0;
    this->cross_tilde_03_b1 = __cross_tilde_03_b1;
    this->cross_tilde_03_b2 = __cross_tilde_03_b2;
    this->cross_tilde_03_oneOverA0 = __cross_tilde_03_oneOverA0;
    this->cross_tilde_03_oneOverA1 = __cross_tilde_03_oneOverA1;
    this->cross_tilde_03_x0 = __cross_tilde_03_x0;
    this->cross_tilde_03_x3 = __cross_tilde_03_x3;
    this->cross_tilde_03_x1 = __cross_tilde_03_x1;
    this->cross_tilde_03_x2 = __cross_tilde_03_x2;
    this->cross_tilde_03_y0L = __cross_tilde_03_y0L;
    this->cross_tilde_03_y1L = __cross_tilde_03_y1L;
    this->cross_tilde_03_y2L = __cross_tilde_03_y2L;
    this->cross_tilde_03_y0H = __cross_tilde_03_y0H;
    this->cross_tilde_03_y1H = __cross_tilde_03_y1H;
    this->cross_tilde_03_y2H = __cross_tilde_03_y2H;
}

void signalsend_06_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_01_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void dspexpr_09_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void signalreceive_12_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void cross_tilde_01_perform(
    const Sample * x,
    const Sample * freq,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    auto __cross_tilde_01_y2H = this->cross_tilde_01_y2H;
    auto __cross_tilde_01_y1H = this->cross_tilde_01_y1H;
    auto __cross_tilde_01_y0H = this->cross_tilde_01_y0H;
    auto __cross_tilde_01_y2L = this->cross_tilde_01_y2L;
    auto __cross_tilde_01_y1L = this->cross_tilde_01_y1L;
    auto __cross_tilde_01_y0L = this->cross_tilde_01_y0L;
    auto __cross_tilde_01_x2 = this->cross_tilde_01_x2;
    auto __cross_tilde_01_x1 = this->cross_tilde_01_x1;
    auto __cross_tilde_01_x3 = this->cross_tilde_01_x3;
    auto __cross_tilde_01_x0 = this->cross_tilde_01_x0;
    auto __cross_tilde_01_oneOverA1 = this->cross_tilde_01_oneOverA1;
    auto __cross_tilde_01_oneOverA0 = this->cross_tilde_01_oneOverA0;
    auto __cross_tilde_01_b2 = this->cross_tilde_01_b2;
    auto __cross_tilde_01_b1 = this->cross_tilde_01_b1;
    auto __cross_tilde_01_b0 = this->cross_tilde_01_b0;
    auto __cross_tilde_01_needsUpdate = this->cross_tilde_01_needsUpdate;
    auto __cross_tilde_01__freq = this->cross_tilde_01__freq;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (__cross_tilde_01__freq != freq[(Index)i] || (bool)(__cross_tilde_01_needsUpdate)) {
            __cross_tilde_01__freq = freq[(Index)i];
            array<number, 5> coeffs = this->cross_tilde_01_calculateCoefficients(__cross_tilde_01__freq);
            __cross_tilde_01_b0 = coeffs[0];
            __cross_tilde_01_b1 = coeffs[1];
            __cross_tilde_01_b2 = coeffs[2];
            __cross_tilde_01_oneOverA0 = coeffs[3];
            __cross_tilde_01_oneOverA1 = coeffs[4];
            __cross_tilde_01_needsUpdate = false;
        }

        __cross_tilde_01_x0 = x[(Index)i];
        number lowPass = (number)((__cross_tilde_01_x0 + __cross_tilde_01_x3 + 3.0 * (__cross_tilde_01_x1 + __cross_tilde_01_x2)) * __cross_tilde_01_oneOverA0 + (__cross_tilde_01_y0L * __cross_tilde_01_b0 + __cross_tilde_01_y1L * __cross_tilde_01_b1 + __cross_tilde_01_y2L * __cross_tilde_01_b2));
        number highPass = (number)((__cross_tilde_01_x3 - __cross_tilde_01_x0 + 3.0 * (__cross_tilde_01_x1 - __cross_tilde_01_x2)) * __cross_tilde_01_oneOverA1 + (__cross_tilde_01_y0H * __cross_tilde_01_b0 + __cross_tilde_01_y1H * __cross_tilde_01_b1 + __cross_tilde_01_y2H * __cross_tilde_01_b2));
        __cross_tilde_01_x3 = __cross_tilde_01_x2;
        __cross_tilde_01_x2 = __cross_tilde_01_x1;
        __cross_tilde_01_x1 = __cross_tilde_01_x0;
        __cross_tilde_01_y2L = __cross_tilde_01_y1L;
        __cross_tilde_01_y1L = __cross_tilde_01_y0L;
        __cross_tilde_01_y0L = fixdenorm(lowPass);
        __cross_tilde_01_y2H = __cross_tilde_01_y1H;
        __cross_tilde_01_y1H = __cross_tilde_01_y0H;
        __cross_tilde_01_y0H = fixdenorm(highPass);
        out1[(Index)i] = lowPass;
        out2[(Index)i] = highPass;
    }

    this->cross_tilde_01__freq = __cross_tilde_01__freq;
    this->cross_tilde_01_needsUpdate = __cross_tilde_01_needsUpdate;
    this->cross_tilde_01_b0 = __cross_tilde_01_b0;
    this->cross_tilde_01_b1 = __cross_tilde_01_b1;
    this->cross_tilde_01_b2 = __cross_tilde_01_b2;
    this->cross_tilde_01_oneOverA0 = __cross_tilde_01_oneOverA0;
    this->cross_tilde_01_oneOverA1 = __cross_tilde_01_oneOverA1;
    this->cross_tilde_01_x0 = __cross_tilde_01_x0;
    this->cross_tilde_01_x3 = __cross_tilde_01_x3;
    this->cross_tilde_01_x1 = __cross_tilde_01_x1;
    this->cross_tilde_01_x2 = __cross_tilde_01_x2;
    this->cross_tilde_01_y0L = __cross_tilde_01_y0L;
    this->cross_tilde_01_y1L = __cross_tilde_01_y1L;
    this->cross_tilde_01_y2L = __cross_tilde_01_y2L;
    this->cross_tilde_01_y0H = __cross_tilde_01_y0H;
    this->cross_tilde_01_y1H = __cross_tilde_01_y1H;
    this->cross_tilde_01_y2H = __cross_tilde_01_y2H;
}

void signalsend_02_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_07_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void dspexpr_07_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_08_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void signalreceive_15_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void signalsend_11_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_06_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void cross_tilde_04_perform(
    const Sample * x,
    const Sample * freq,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    auto __cross_tilde_04_y2H = this->cross_tilde_04_y2H;
    auto __cross_tilde_04_y1H = this->cross_tilde_04_y1H;
    auto __cross_tilde_04_y0H = this->cross_tilde_04_y0H;
    auto __cross_tilde_04_y2L = this->cross_tilde_04_y2L;
    auto __cross_tilde_04_y1L = this->cross_tilde_04_y1L;
    auto __cross_tilde_04_y0L = this->cross_tilde_04_y0L;
    auto __cross_tilde_04_x2 = this->cross_tilde_04_x2;
    auto __cross_tilde_04_x1 = this->cross_tilde_04_x1;
    auto __cross_tilde_04_x3 = this->cross_tilde_04_x3;
    auto __cross_tilde_04_x0 = this->cross_tilde_04_x0;
    auto __cross_tilde_04_oneOverA1 = this->cross_tilde_04_oneOverA1;
    auto __cross_tilde_04_oneOverA0 = this->cross_tilde_04_oneOverA0;
    auto __cross_tilde_04_b2 = this->cross_tilde_04_b2;
    auto __cross_tilde_04_b1 = this->cross_tilde_04_b1;
    auto __cross_tilde_04_b0 = this->cross_tilde_04_b0;
    auto __cross_tilde_04_needsUpdate = this->cross_tilde_04_needsUpdate;
    auto __cross_tilde_04__freq = this->cross_tilde_04__freq;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (__cross_tilde_04__freq != freq[(Index)i] || (bool)(__cross_tilde_04_needsUpdate)) {
            __cross_tilde_04__freq = freq[(Index)i];
            array<number, 5> coeffs = this->cross_tilde_04_calculateCoefficients(__cross_tilde_04__freq);
            __cross_tilde_04_b0 = coeffs[0];
            __cross_tilde_04_b1 = coeffs[1];
            __cross_tilde_04_b2 = coeffs[2];
            __cross_tilde_04_oneOverA0 = coeffs[3];
            __cross_tilde_04_oneOverA1 = coeffs[4];
            __cross_tilde_04_needsUpdate = false;
        }

        __cross_tilde_04_x0 = x[(Index)i];
        number lowPass = (number)((__cross_tilde_04_x0 + __cross_tilde_04_x3 + 3.0 * (__cross_tilde_04_x1 + __cross_tilde_04_x2)) * __cross_tilde_04_oneOverA0 + (__cross_tilde_04_y0L * __cross_tilde_04_b0 + __cross_tilde_04_y1L * __cross_tilde_04_b1 + __cross_tilde_04_y2L * __cross_tilde_04_b2));
        number highPass = (number)((__cross_tilde_04_x3 - __cross_tilde_04_x0 + 3.0 * (__cross_tilde_04_x1 - __cross_tilde_04_x2)) * __cross_tilde_04_oneOverA1 + (__cross_tilde_04_y0H * __cross_tilde_04_b0 + __cross_tilde_04_y1H * __cross_tilde_04_b1 + __cross_tilde_04_y2H * __cross_tilde_04_b2));
        __cross_tilde_04_x3 = __cross_tilde_04_x2;
        __cross_tilde_04_x2 = __cross_tilde_04_x1;
        __cross_tilde_04_x1 = __cross_tilde_04_x0;
        __cross_tilde_04_y2L = __cross_tilde_04_y1L;
        __cross_tilde_04_y1L = __cross_tilde_04_y0L;
        __cross_tilde_04_y0L = fixdenorm(lowPass);
        __cross_tilde_04_y2H = __cross_tilde_04_y1H;
        __cross_tilde_04_y1H = __cross_tilde_04_y0H;
        __cross_tilde_04_y0H = fixdenorm(highPass);
        out1[(Index)i] = lowPass;
        out2[(Index)i] = highPass;
    }

    this->cross_tilde_04__freq = __cross_tilde_04__freq;
    this->cross_tilde_04_needsUpdate = __cross_tilde_04_needsUpdate;
    this->cross_tilde_04_b0 = __cross_tilde_04_b0;
    this->cross_tilde_04_b1 = __cross_tilde_04_b1;
    this->cross_tilde_04_b2 = __cross_tilde_04_b2;
    this->cross_tilde_04_oneOverA0 = __cross_tilde_04_oneOverA0;
    this->cross_tilde_04_oneOverA1 = __cross_tilde_04_oneOverA1;
    this->cross_tilde_04_x0 = __cross_tilde_04_x0;
    this->cross_tilde_04_x3 = __cross_tilde_04_x3;
    this->cross_tilde_04_x1 = __cross_tilde_04_x1;
    this->cross_tilde_04_x2 = __cross_tilde_04_x2;
    this->cross_tilde_04_y0L = __cross_tilde_04_y0L;
    this->cross_tilde_04_y1L = __cross_tilde_04_y1L;
    this->cross_tilde_04_y2L = __cross_tilde_04_y2L;
    this->cross_tilde_04_y0H = __cross_tilde_04_y0H;
    this->cross_tilde_04_y1H = __cross_tilde_04_y1H;
    this->cross_tilde_04_y2H = __cross_tilde_04_y2H;
}

void signalsend_08_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_04_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void dspexpr_16_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void signalreceive_14_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void signalsend_09_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_10_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void dspexpr_23_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void signalreceive_13_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void cross_tilde_02_perform(
    const Sample * x,
    const Sample * freq,
    SampleValue * out1,
    SampleValue * out2,
    Index n
) {
    auto __cross_tilde_02_y2H = this->cross_tilde_02_y2H;
    auto __cross_tilde_02_y1H = this->cross_tilde_02_y1H;
    auto __cross_tilde_02_y0H = this->cross_tilde_02_y0H;
    auto __cross_tilde_02_y2L = this->cross_tilde_02_y2L;
    auto __cross_tilde_02_y1L = this->cross_tilde_02_y1L;
    auto __cross_tilde_02_y0L = this->cross_tilde_02_y0L;
    auto __cross_tilde_02_x2 = this->cross_tilde_02_x2;
    auto __cross_tilde_02_x1 = this->cross_tilde_02_x1;
    auto __cross_tilde_02_x3 = this->cross_tilde_02_x3;
    auto __cross_tilde_02_x0 = this->cross_tilde_02_x0;
    auto __cross_tilde_02_oneOverA1 = this->cross_tilde_02_oneOverA1;
    auto __cross_tilde_02_oneOverA0 = this->cross_tilde_02_oneOverA0;
    auto __cross_tilde_02_b2 = this->cross_tilde_02_b2;
    auto __cross_tilde_02_b1 = this->cross_tilde_02_b1;
    auto __cross_tilde_02_b0 = this->cross_tilde_02_b0;
    auto __cross_tilde_02_needsUpdate = this->cross_tilde_02_needsUpdate;
    auto __cross_tilde_02__freq = this->cross_tilde_02__freq;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (__cross_tilde_02__freq != freq[(Index)i] || (bool)(__cross_tilde_02_needsUpdate)) {
            __cross_tilde_02__freq = freq[(Index)i];
            array<number, 5> coeffs = this->cross_tilde_02_calculateCoefficients(__cross_tilde_02__freq);
            __cross_tilde_02_b0 = coeffs[0];
            __cross_tilde_02_b1 = coeffs[1];
            __cross_tilde_02_b2 = coeffs[2];
            __cross_tilde_02_oneOverA0 = coeffs[3];
            __cross_tilde_02_oneOverA1 = coeffs[4];
            __cross_tilde_02_needsUpdate = false;
        }

        __cross_tilde_02_x0 = x[(Index)i];
        number lowPass = (number)((__cross_tilde_02_x0 + __cross_tilde_02_x3 + 3.0 * (__cross_tilde_02_x1 + __cross_tilde_02_x2)) * __cross_tilde_02_oneOverA0 + (__cross_tilde_02_y0L * __cross_tilde_02_b0 + __cross_tilde_02_y1L * __cross_tilde_02_b1 + __cross_tilde_02_y2L * __cross_tilde_02_b2));
        number highPass = (number)((__cross_tilde_02_x3 - __cross_tilde_02_x0 + 3.0 * (__cross_tilde_02_x1 - __cross_tilde_02_x2)) * __cross_tilde_02_oneOverA1 + (__cross_tilde_02_y0H * __cross_tilde_02_b0 + __cross_tilde_02_y1H * __cross_tilde_02_b1 + __cross_tilde_02_y2H * __cross_tilde_02_b2));
        __cross_tilde_02_x3 = __cross_tilde_02_x2;
        __cross_tilde_02_x2 = __cross_tilde_02_x1;
        __cross_tilde_02_x1 = __cross_tilde_02_x0;
        __cross_tilde_02_y2L = __cross_tilde_02_y1L;
        __cross_tilde_02_y1L = __cross_tilde_02_y0L;
        __cross_tilde_02_y0L = fixdenorm(lowPass);
        __cross_tilde_02_y2H = __cross_tilde_02_y1H;
        __cross_tilde_02_y1H = __cross_tilde_02_y0H;
        __cross_tilde_02_y0H = fixdenorm(highPass);
        out1[(Index)i] = lowPass;
        out2[(Index)i] = highPass;
    }

    this->cross_tilde_02__freq = __cross_tilde_02__freq;
    this->cross_tilde_02_needsUpdate = __cross_tilde_02_needsUpdate;
    this->cross_tilde_02_b0 = __cross_tilde_02_b0;
    this->cross_tilde_02_b1 = __cross_tilde_02_b1;
    this->cross_tilde_02_b2 = __cross_tilde_02_b2;
    this->cross_tilde_02_oneOverA0 = __cross_tilde_02_oneOverA0;
    this->cross_tilde_02_oneOverA1 = __cross_tilde_02_oneOverA1;
    this->cross_tilde_02_x0 = __cross_tilde_02_x0;
    this->cross_tilde_02_x3 = __cross_tilde_02_x3;
    this->cross_tilde_02_x1 = __cross_tilde_02_x1;
    this->cross_tilde_02_x2 = __cross_tilde_02_x2;
    this->cross_tilde_02_y0L = __cross_tilde_02_y0L;
    this->cross_tilde_02_y1L = __cross_tilde_02_y1L;
    this->cross_tilde_02_y2L = __cross_tilde_02_y2L;
    this->cross_tilde_02_y0H = __cross_tilde_02_y0H;
    this->cross_tilde_02_y1H = __cross_tilde_02_y1H;
    this->cross_tilde_02_y2H = __cross_tilde_02_y2H;
}

void signalsend_03_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_03_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void dspexpr_11_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_10_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_13_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void signalreceive_09_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void signalsend_04_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_05_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void dspexpr_20_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_15_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_18_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_19_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * 0.5;//#map:_###_obj_###_:1
    }
}

void signalsend_07_perform(const SampleValue * input, SampleValue * send, Index n) {
    for (Index i = 0; i < n; i++) {
        send[(Index)i] = input[(Index)i];
    }
}

void signalreceive_11_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void signalreceive_08_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void signalreceive_16_perform(const SampleValue * receive, SampleValue * output, Index n) {
    for (Index i = 0; i < n; i++) {
        output[(Index)i] = receive[(Index)i];
    }
}

void p_01_perform(
    const SampleValue * in1,
    const SampleValue * in2,
    const SampleValue * in3,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    SampleValue * out4,
    SampleValue * out5,
    SampleValue * out6,
    SampleValue * out7,
    SampleValue * out8,
    SampleValue * out9,
    Index n
) {
    // subpatcher: fft_analysis
    ConstSampleArray<3> ins = {in1, in2, in3};

    SampleArray<9> outs = {out1, out2, out3, out4, out5, out6, out7, out8, out9};
    this->p_01->process(ins, 3, outs, 9, n);
}

void codebox_tilde_05_perform(
    number in1,
    number in2,
    number in3,
    const Sample * in4,
    const Sample * in5,
    const Sample * in6,
    const Sample * in7,
    const Sample * in8,
    const Sample * in9,
    const Sample * in10,
    const Sample * in11,
    const Sample * in12,
    number in13,
    number in14,
    SampleValue * out1,
    SampleValue * out2,
    SampleValue * out3,
    SampleValue * out4,
    SampleValue * out5,
    SampleValue * out6,
    SampleValue * out7,
    SampleValue * out8,
    SampleValue * out9,
    Index n
) {
    number lowScale = in1;
    number bodyScale = in2;
    number airScale = in3;
    number rawLowSplit = in13;
    number rawHighSplit = in14;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number lowRateIn = in4[(Index)i];
        number midRateIn = in5[(Index)i];
        number highRateIn = in6[(Index)i];
        number lowDepthIn = in7[(Index)i];
        number midDepthIn = in8[(Index)i];
        number highDepthIn = in9[(Index)i];
        number lowDutyIn = in10[(Index)i];
        number midDutyIn = in11[(Index)i];
        number highDutyIn = in12[(Index)i];
        number lowRate = (0.6 + (lowRateIn - 0.6) * lowScale > 3 ? 3 : (0.6 + (lowRateIn - 0.6) * lowScale < 0.6 ? 0.6 : 0.6 + (lowRateIn - 0.6) * lowScale));
        number midRate = (2 + (midRateIn - 2) * bodyScale > 9 ? 9 : (2 + (midRateIn - 2) * bodyScale < 2 ? 2 : 2 + (midRateIn - 2) * bodyScale));
        number highRate = (5 + (highRateIn - 5) * airScale > 18 ? 18 : (5 + (highRateIn - 5) * airScale < 5 ? 5 : 5 + (highRateIn - 5) * airScale));
        number lowDepth = (0.2 + (lowDepthIn - 0.2) * lowScale > 0.55 ? 0.55 : (0.2 + (lowDepthIn - 0.2) * lowScale < 0.2 ? 0.2 : 0.2 + (lowDepthIn - 0.2) * lowScale));
        number midDepth = (0.35 + (midDepthIn - 0.35) * bodyScale > 0.85 ? 0.85 : (0.35 + (midDepthIn - 0.35) * bodyScale < 0.35 ? 0.35 : 0.35 + (midDepthIn - 0.35) * bodyScale));
        number highDepth = (0.15 + (highDepthIn - 0.15) * airScale > 0.6 ? 0.6 : (0.15 + (highDepthIn - 0.15) * airScale < 0.15 ? 0.15 : 0.15 + (highDepthIn - 0.15) * airScale));
        number lowDuty = (0.75 - (0.75 - lowDutyIn) * lowScale > 0.95 ? 0.95 : (0.75 - (0.75 - lowDutyIn) * lowScale < 0.05 ? 0.05 : 0.75 - (0.75 - lowDutyIn) * lowScale));
        number midDuty = (0.6 - (0.6 - midDutyIn) * bodyScale > 0.95 ? 0.95 : (0.6 - (0.6 - midDutyIn) * bodyScale < 0.05 ? 0.05 : 0.6 - (0.6 - midDutyIn) * bodyScale));
        number highDuty = (0.35 - (0.35 - highDutyIn) * airScale > 0.95 ? 0.95 : (0.35 - (0.35 - highDutyIn) * airScale < 0.05 ? 0.05 : 0.35 - (0.35 - highDutyIn) * airScale));
        number lowActive = rawLowSplit > 0.001;
        number highActive = rawHighSplit > 0.001;

        if ((bool)(!(bool)(lowActive)) && (bool)(!(bool)(highActive))) {
            number sharedRate = (lowRate + midRate + highRate) * 0.33333333;
            number sharedDepth = (lowDepth + midDepth + highDepth) * 0.33333333;
            number sharedDuty = (lowDuty + midDuty + highDuty) * 0.33333333;
            lowRate = sharedRate;//#map:_###_obj_###_:40
            midRate = sharedRate;//#map:_###_obj_###_:41
            highRate = sharedRate;//#map:_###_obj_###_:42
            lowDepth = sharedDepth;//#map:_###_obj_###_:44
            midDepth = sharedDepth;//#map:_###_obj_###_:45
            highDepth = sharedDepth;//#map:_###_obj_###_:46
            lowDuty = sharedDuty;//#map:_###_obj_###_:48
            midDuty = sharedDuty;//#map:_###_obj_###_:49
            highDuty = sharedDuty;//#map:_###_obj_###_:50
        } else if ((bool)(lowActive) && (bool)(!(bool)(highActive))) {
            number upperRate = (midRate + highRate) * 0.5;
            number upperDepth = (midDepth + highDepth) * 0.5;
            number upperDuty = (midDuty + highDuty) * 0.5;
            midRate = upperRate;//#map:_###_obj_###_:56
            highRate = upperRate;//#map:_###_obj_###_:57
            midDepth = upperDepth;//#map:_###_obj_###_:59
            highDepth = upperDepth;//#map:_###_obj_###_:60
            midDuty = upperDuty;//#map:_###_obj_###_:62
            highDuty = upperDuty;//#map:_###_obj_###_:63
        } else if ((bool)(!(bool)(lowActive)) && (bool)(highActive)) {
            number lowerRate = (lowRate + midRate) * 0.5;
            number lowerDepth = (lowDepth + midDepth) * 0.5;
            number lowerDuty = (lowDuty + midDuty) * 0.5;
            lowRate = lowerRate;//#map:_###_obj_###_:69
            midRate = lowerRate;//#map:_###_obj_###_:70
            lowDepth = lowerDepth;//#map:_###_obj_###_:72
            midDepth = lowerDepth;//#map:_###_obj_###_:73
            lowDuty = lowerDuty;//#map:_###_obj_###_:75
            midDuty = lowerDuty;//#map:_###_obj_###_:76
        }//#map:_###_obj_###_:64//#map:_###_obj_###_:51//#map:_###_obj_###_:35

        out1[(Index)i] = lowRate;//#map:_###_obj_###_:79
        out2[(Index)i] = midRate;//#map:_###_obj_###_:80
        out3[(Index)i] = highRate;//#map:_###_obj_###_:81
        out4[(Index)i] = lowDepth;//#map:_###_obj_###_:82
        out5[(Index)i] = midDepth;//#map:_###_obj_###_:83
        out6[(Index)i] = highDepth;//#map:_###_obj_###_:84
        out7[(Index)i] = lowDuty;//#map:_###_obj_###_:85
        out8[(Index)i] = midDuty;//#map:_###_obj_###_:86
        out9[(Index)i] = highDuty;//#map:_###_obj_###_:87
    }
}

void dspexpr_12_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void phasor_01_perform(const Sample * freq, SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->phasor_01_ph_next(freq[(Index)i], -1);
        this->phasor_01_sigbuf[(Index)i] = -1;
    }
}

void selector_01_perform(
    number onoff,
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (onoff >= 1 && onoff < 2)
            out[(Index)i] = in1[(Index)i];
        else if (onoff >= 2 && onoff < 3)
            out[(Index)i] = in2[(Index)i];
        else
            out[(Index)i] = 0;
    }
}

void dspexpr_14_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void phasor_02_perform(const Sample * freq, SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->phasor_02_ph_next(freq[(Index)i], -1);
        this->phasor_02_sigbuf[(Index)i] = -1;
    }
}

void selector_02_perform(
    number onoff,
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (onoff >= 1 && onoff < 2)
            out[(Index)i] = in1[(Index)i];
        else if (onoff >= 2 && onoff < 3)
            out[(Index)i] = in2[(Index)i];
        else
            out[(Index)i] = 0;
    }
}

void dspexpr_17_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void phasor_03_perform(const Sample * freq, SampleValue * out, Index n) {
    for (Index i = 0; i < n; i++) {
        out[(Index)i] = this->phasor_03_ph_next(freq[(Index)i], -1);
        this->phasor_03_sigbuf[(Index)i] = -1;
    }
}

void selector_03_perform(
    number onoff,
    const SampleValue * in1,
    const SampleValue * in2,
    SampleValue * out,
    Index n
) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        if (onoff >= 1 && onoff < 2)
            out[(Index)i] = in1[(Index)i];
        else if (onoff >= 2 && onoff < 3)
            out[(Index)i] = in2[(Index)i];
        else
            out[(Index)i] = 0;
    }
}

void dspexpr_37_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_36_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_35_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 0.95 ? 0.95 : (in1[(Index)i] < 0 ? 0 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void dspexpr_26_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_25_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_24_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 0.95 ? 0.95 : (in1[(Index)i] < 0 ? 0 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void dspexpr_40_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_39_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_38_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 0.95 ? 0.95 : (in1[(Index)i] < 0 ? 0 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void dspexpr_27_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_29_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_28_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 0.95 ? 0.95 : (in1[(Index)i] < 0 ? 0 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void dspexpr_43_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_42_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_41_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 0.95 ? 0.95 : (in1[(Index)i] < 0 ? 0 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void dspexpr_32_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] * in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_31_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_30_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 0.95 ? 0.95 : (in1[(Index)i] < 0 ? 0 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void dspexpr_45_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] - in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_44_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 0.95 ? 0.95 : (in1[(Index)i] < 0.05 ? 0.05 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void gen_04_perform(
    const Sample * in1,
    const Sample * in2,
    const Sample * in3,
    const Sample * in4,
    number in5,
    SampleValue * out1,
    Index n
) {
    number constant_1_0 = 1;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number sub_2_1 = constant_1_0 - in2[(Index)i];
        number lt_3_2 = in3[(Index)i] < in4[(Index)i];
        number slide_4_4 = this->gen_04_slide_3_next(lt_3_2, in5, in5);
        number mul_5_5 = in2[(Index)i] * slide_4_4;
        number add_6_6 = sub_2_1 + mul_5_5;
        number mul_7_7 = in1[(Index)i] * add_6_6;
        out1[(Index)i] = mul_7_7;
    }
}

void gen_01_perform(
    const Sample * in1,
    const Sample * in2,
    const Sample * in3,
    const Sample * in4,
    number in5,
    SampleValue * out1,
    Index n
) {
    number constant_1_0 = 1;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number sub_2_1 = constant_1_0 - in2[(Index)i];
        number lt_3_2 = in3[(Index)i] < in4[(Index)i];
        number slide_4_4 = this->gen_01_slide_3_next(lt_3_2, in5, in5);
        number mul_5_5 = in2[(Index)i] * slide_4_4;
        number add_6_6 = sub_2_1 + mul_5_5;
        number mul_7_7 = in1[(Index)i] * add_6_6;
        out1[(Index)i] = mul_7_7;
    }
}

void dspexpr_47_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] - in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_46_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 0.95 ? 0.95 : (in1[(Index)i] < 0.05 ? 0.05 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void gen_06_perform(
    const Sample * in1,
    const Sample * in2,
    const Sample * in3,
    const Sample * in4,
    number in5,
    SampleValue * out1,
    Index n
) {
    number constant_1_0 = 1;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number sub_2_1 = constant_1_0 - in2[(Index)i];
        number lt_3_2 = in3[(Index)i] < in4[(Index)i];
        number slide_4_4 = this->gen_06_slide_3_next(lt_3_2, in5, in5);
        number mul_5_5 = in2[(Index)i] * slide_4_4;
        number add_6_6 = sub_2_1 + mul_5_5;
        number mul_7_7 = in1[(Index)i] * add_6_6;
        out1[(Index)i] = mul_7_7;
    }
}

void dspexpr_34_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void gen_03_perform(
    const Sample * in1,
    const Sample * in2,
    const Sample * in3,
    const Sample * in4,
    number in5,
    SampleValue * out1,
    Index n
) {
    number constant_1_0 = 1;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number sub_2_1 = constant_1_0 - in2[(Index)i];
        number lt_3_2 = in3[(Index)i] < in4[(Index)i];
        number slide_4_4 = this->gen_03_slide_3_next(lt_3_2, in5, in5);
        number mul_5_5 = in2[(Index)i] * slide_4_4;
        number add_6_6 = sub_2_1 + mul_5_5;
        number mul_7_7 = in1[(Index)i] * add_6_6;
        out1[(Index)i] = mul_7_7;
    }
}

void dspexpr_22_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void dspexpr_49_perform(const Sample * in1, number in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] - in2;//#map:_###_obj_###_:1
    }
}

void dspexpr_48_perform(const Sample * in1, number in2, number in3, SampleValue * out1, Index n) {
    RNBO_UNUSED(in3);
    RNBO_UNUSED(in2);
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = (in1[(Index)i] > 0.95 ? 0.95 : (in1[(Index)i] < 0.05 ? 0.05 : in1[(Index)i]));//#map:_###_obj_###_:1
    }
}

void gen_05_perform(
    const Sample * in1,
    const Sample * in2,
    const Sample * in3,
    const Sample * in4,
    number in5,
    SampleValue * out1,
    Index n
) {
    number constant_1_0 = 1;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number sub_2_1 = constant_1_0 - in2[(Index)i];
        number lt_3_2 = in3[(Index)i] < in4[(Index)i];
        number slide_4_4 = this->gen_05_slide_3_next(lt_3_2, in5, in5);
        number mul_5_5 = in2[(Index)i] * slide_4_4;
        number add_6_6 = sub_2_1 + mul_5_5;
        number mul_7_7 = in1[(Index)i] * add_6_6;
        out1[(Index)i] = mul_7_7;
    }
}

void dspexpr_33_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void gen_02_perform(
    const Sample * in1,
    const Sample * in2,
    const Sample * in3,
    const Sample * in4,
    number in5,
    SampleValue * out1,
    Index n
) {
    number constant_1_0 = 1;
    Index i;

    for (i = 0; i < (Index)n; i++) {
        number sub_2_1 = constant_1_0 - in2[(Index)i];
        number lt_3_2 = in3[(Index)i] < in4[(Index)i];
        number slide_4_4 = this->gen_02_slide_3_next(lt_3_2, in5, in5);
        number mul_5_5 = in2[(Index)i] * slide_4_4;
        number add_6_6 = sub_2_1 + mul_5_5;
        number mul_7_7 = in1[(Index)i] * add_6_6;
        out1[(Index)i] = mul_7_7;
    }
}

void dspexpr_21_perform(const Sample * in1, const Sample * in2, SampleValue * out1, Index n) {
    Index i;

    for (i = 0; i < (Index)n; i++) {
        out1[(Index)i] = in1[(Index)i] + in2[(Index)i];//#map:_###_obj_###_:1
    }
}

void stackprotect_perform(Index n) {
    RNBO_UNUSED(n);
    auto __stackprotect_count = this->stackprotect_count;
    __stackprotect_count = 0;
    this->stackprotect_count = __stackprotect_count;
}

void numberobj_01_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_01_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_01_value = localvalue;
}

void numberobj_02_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_02_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_02_value = localvalue;
}

void numberobj_03_value_setter(number v) {
    number localvalue = v;

    if (this->numberobj_03_currentFormat != 6) {
        localvalue = trunc(localvalue);
    }

    this->numberobj_03_value = localvalue;
}

array<number, 2> cross_tilde_01_complexDivide(number aReal, number aImag, number bReal, number bImag) {
    number denom = (number)(bReal * bReal + bImag * bImag);

    return {
        (aReal * bReal + aImag * bImag) / denom,
        (aImag * bReal - aReal * bImag) / denom
    };
}

array<number, 2> cross_tilde_01_complexMultiply(number aReal, number aImag, number bReal, number bImag) {
    return {aReal * bReal - aImag * bImag, aReal * bImag + aImag * bReal};
}

array<number, 5> cross_tilde_01_calculateCoefficients(number freq) {
    freq = (freq > this->sr * 0.5 ? this->sr * 0.5 : (freq < 1 ? 1 : freq));
    number omega2 = (number)(3.14159265358979323846 * freq / this->sr);
    number t = (number)(rnbo_sin(omega2) / rnbo_cos(omega2));
    array<number, 2> z0 = this->cross_tilde_01_complexDivide(1. - 0.5 * t, 0.866025403784 * t, 1. + 0.5 * t, -0.866025403784 * t);
    array<number, 2> z1 = {(1. - t) / (1. + t), 0.};
    array<number, 2> z2 = {z0[0], -z0[1]};
    number b0Coeff = (number)(z0[0] + z1[0] + z2[0]);
    number b1Coeff = (number)(z0[0] * z1[0] - z0[1] * z1[1] + (z0[0] * z2[0] - z0[1] * z2[1]));
    array<number, 2> n = this->cross_tilde_01_complexMultiply(z1[0], z1[1], z2[0], z2[1]);
    b1Coeff += n[0];
    array<number, 2> d = this->cross_tilde_01_complexMultiply(n[0], n[1], z0[0], z0[1]);
    number b2Coeff = (number)(d[0]);
    number oneOverA0 = (number)((1.0 - b0Coeff + b1Coeff - b2Coeff) / (number)8);
    number oneOverA1 = (number)((1.0 + b0Coeff + b1Coeff + b2Coeff) / (number)8);
    b1Coeff = 0 - b1Coeff;
    return {b0Coeff, b1Coeff, b2Coeff, oneOverA0, oneOverA1};
}

void cross_tilde_01_clear() {
    this->cross_tilde_01_x0 = 0;
    this->cross_tilde_01_x1 = 0;
    this->cross_tilde_01_x2 = 0;
    this->cross_tilde_01_x3 = 0;
    this->cross_tilde_01_y0L = 0;
    this->cross_tilde_01_y1L = 0;
    this->cross_tilde_01_y2L = 0;
    this->cross_tilde_01_y0H = 0;
    this->cross_tilde_01_y1H = 0;
    this->cross_tilde_01_y2H = 0;
}

void cross_tilde_01_reset() {
    this->cross_tilde_01_clear();
    this->cross_tilde_01_needsUpdate = true;
}

void cross_tilde_01_dspsetup(bool force) {
    if ((bool)(this->cross_tilde_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cross_tilde_01_reset();
    this->cross_tilde_01_setupDone = true;
}

array<number, 2> cross_tilde_02_complexDivide(number aReal, number aImag, number bReal, number bImag) {
    number denom = (number)(bReal * bReal + bImag * bImag);

    return {
        (aReal * bReal + aImag * bImag) / denom,
        (aImag * bReal - aReal * bImag) / denom
    };
}

array<number, 2> cross_tilde_02_complexMultiply(number aReal, number aImag, number bReal, number bImag) {
    return {aReal * bReal - aImag * bImag, aReal * bImag + aImag * bReal};
}

array<number, 5> cross_tilde_02_calculateCoefficients(number freq) {
    freq = (freq > this->sr * 0.5 ? this->sr * 0.5 : (freq < 1 ? 1 : freq));
    number omega2 = (number)(3.14159265358979323846 * freq / this->sr);
    number t = (number)(rnbo_sin(omega2) / rnbo_cos(omega2));
    array<number, 2> z0 = this->cross_tilde_02_complexDivide(1. - 0.5 * t, 0.866025403784 * t, 1. + 0.5 * t, -0.866025403784 * t);
    array<number, 2> z1 = {(1. - t) / (1. + t), 0.};
    array<number, 2> z2 = {z0[0], -z0[1]};
    number b0Coeff = (number)(z0[0] + z1[0] + z2[0]);
    number b1Coeff = (number)(z0[0] * z1[0] - z0[1] * z1[1] + (z0[0] * z2[0] - z0[1] * z2[1]));
    array<number, 2> n = this->cross_tilde_02_complexMultiply(z1[0], z1[1], z2[0], z2[1]);
    b1Coeff += n[0];
    array<number, 2> d = this->cross_tilde_02_complexMultiply(n[0], n[1], z0[0], z0[1]);
    number b2Coeff = (number)(d[0]);
    number oneOverA0 = (number)((1.0 - b0Coeff + b1Coeff - b2Coeff) / (number)8);
    number oneOverA1 = (number)((1.0 + b0Coeff + b1Coeff + b2Coeff) / (number)8);
    b1Coeff = 0 - b1Coeff;
    return {b0Coeff, b1Coeff, b2Coeff, oneOverA0, oneOverA1};
}

void cross_tilde_02_clear() {
    this->cross_tilde_02_x0 = 0;
    this->cross_tilde_02_x1 = 0;
    this->cross_tilde_02_x2 = 0;
    this->cross_tilde_02_x3 = 0;
    this->cross_tilde_02_y0L = 0;
    this->cross_tilde_02_y1L = 0;
    this->cross_tilde_02_y2L = 0;
    this->cross_tilde_02_y0H = 0;
    this->cross_tilde_02_y1H = 0;
    this->cross_tilde_02_y2H = 0;
}

void cross_tilde_02_reset() {
    this->cross_tilde_02_clear();
    this->cross_tilde_02_needsUpdate = true;
}

void cross_tilde_02_dspsetup(bool force) {
    if ((bool)(this->cross_tilde_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cross_tilde_02_reset();
    this->cross_tilde_02_setupDone = true;
}

void numberobj_01_init() {
    this->numberobj_01_currentFormat = 6;
}

void numberobj_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_01_value;
}

void numberobj_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_01_value_set(preset["value"]);
}

void phasor_01_onBeatTimeChanged(number beattime) {
    RNBO_UNUSED(beattime);
    this->phasor_01_recalcInc = true;
    this->phasor_01_recalcPhase = true;
}

number phasor_01_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->phasor_01_ph_conv;

    if (this->phasor_01_ph_currentPhase < 0.)
        this->phasor_01_ph_currentPhase = 1. + this->phasor_01_ph_currentPhase;

    if (this->phasor_01_ph_currentPhase > 1.)
        this->phasor_01_ph_currentPhase = this->phasor_01_ph_currentPhase - 1.;

    number tmp = this->phasor_01_ph_currentPhase;
    this->phasor_01_ph_currentPhase += pincr;
    return tmp;
}

void phasor_01_ph_reset() {
    this->phasor_01_ph_currentPhase = 0;
}

void phasor_01_ph_dspsetup() {
    this->phasor_01_ph_conv = (number)1 / this->sr;
}

void phasor_01_dspsetup(bool force) {
    if ((bool)(this->phasor_01_setupDone) && (bool)(!(bool)(force)))
        return;

    this->phasor_01_setupDone = true;
    this->phasor_01_ph_dspsetup();
}

void numberobj_02_init() {
    this->numberobj_02_currentFormat = 6;
}

void numberobj_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_02_value;
}

void numberobj_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_02_value_set(preset["value"]);
}

array<number, 2> cross_tilde_03_complexDivide(number aReal, number aImag, number bReal, number bImag) {
    number denom = (number)(bReal * bReal + bImag * bImag);

    return {
        (aReal * bReal + aImag * bImag) / denom,
        (aImag * bReal - aReal * bImag) / denom
    };
}

array<number, 2> cross_tilde_03_complexMultiply(number aReal, number aImag, number bReal, number bImag) {
    return {aReal * bReal - aImag * bImag, aReal * bImag + aImag * bReal};
}

array<number, 5> cross_tilde_03_calculateCoefficients(number freq) {
    freq = (freq > this->sr * 0.5 ? this->sr * 0.5 : (freq < 1 ? 1 : freq));
    number omega2 = (number)(3.14159265358979323846 * freq / this->sr);
    number t = (number)(rnbo_sin(omega2) / rnbo_cos(omega2));
    array<number, 2> z0 = this->cross_tilde_03_complexDivide(1. - 0.5 * t, 0.866025403784 * t, 1. + 0.5 * t, -0.866025403784 * t);
    array<number, 2> z1 = {(1. - t) / (1. + t), 0.};
    array<number, 2> z2 = {z0[0], -z0[1]};
    number b0Coeff = (number)(z0[0] + z1[0] + z2[0]);
    number b1Coeff = (number)(z0[0] * z1[0] - z0[1] * z1[1] + (z0[0] * z2[0] - z0[1] * z2[1]));
    array<number, 2> n = this->cross_tilde_03_complexMultiply(z1[0], z1[1], z2[0], z2[1]);
    b1Coeff += n[0];
    array<number, 2> d = this->cross_tilde_03_complexMultiply(n[0], n[1], z0[0], z0[1]);
    number b2Coeff = (number)(d[0]);
    number oneOverA0 = (number)((1.0 - b0Coeff + b1Coeff - b2Coeff) / (number)8);
    number oneOverA1 = (number)((1.0 + b0Coeff + b1Coeff + b2Coeff) / (number)8);
    b1Coeff = 0 - b1Coeff;
    return {b0Coeff, b1Coeff, b2Coeff, oneOverA0, oneOverA1};
}

void cross_tilde_03_clear() {
    this->cross_tilde_03_x0 = 0;
    this->cross_tilde_03_x1 = 0;
    this->cross_tilde_03_x2 = 0;
    this->cross_tilde_03_x3 = 0;
    this->cross_tilde_03_y0L = 0;
    this->cross_tilde_03_y1L = 0;
    this->cross_tilde_03_y2L = 0;
    this->cross_tilde_03_y0H = 0;
    this->cross_tilde_03_y1H = 0;
    this->cross_tilde_03_y2H = 0;
}

void cross_tilde_03_reset() {
    this->cross_tilde_03_clear();
    this->cross_tilde_03_needsUpdate = true;
}

void cross_tilde_03_dspsetup(bool force) {
    if ((bool)(this->cross_tilde_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cross_tilde_03_reset();
    this->cross_tilde_03_setupDone = true;
}

void phasor_02_onBeatTimeChanged(number beattime) {
    RNBO_UNUSED(beattime);
    this->phasor_02_recalcInc = true;
    this->phasor_02_recalcPhase = true;
}

number phasor_02_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->phasor_02_ph_conv;

    if (this->phasor_02_ph_currentPhase < 0.)
        this->phasor_02_ph_currentPhase = 1. + this->phasor_02_ph_currentPhase;

    if (this->phasor_02_ph_currentPhase > 1.)
        this->phasor_02_ph_currentPhase = this->phasor_02_ph_currentPhase - 1.;

    number tmp = this->phasor_02_ph_currentPhase;
    this->phasor_02_ph_currentPhase += pincr;
    return tmp;
}

void phasor_02_ph_reset() {
    this->phasor_02_ph_currentPhase = 0;
}

void phasor_02_ph_dspsetup() {
    this->phasor_02_ph_conv = (number)1 / this->sr;
}

void phasor_02_dspsetup(bool force) {
    if ((bool)(this->phasor_02_setupDone) && (bool)(!(bool)(force)))
        return;

    this->phasor_02_setupDone = true;
    this->phasor_02_ph_dspsetup();
}

array<number, 2> cross_tilde_04_complexDivide(number aReal, number aImag, number bReal, number bImag) {
    number denom = (number)(bReal * bReal + bImag * bImag);

    return {
        (aReal * bReal + aImag * bImag) / denom,
        (aImag * bReal - aReal * bImag) / denom
    };
}

array<number, 2> cross_tilde_04_complexMultiply(number aReal, number aImag, number bReal, number bImag) {
    return {aReal * bReal - aImag * bImag, aReal * bImag + aImag * bReal};
}

array<number, 5> cross_tilde_04_calculateCoefficients(number freq) {
    freq = (freq > this->sr * 0.5 ? this->sr * 0.5 : (freq < 1 ? 1 : freq));
    number omega2 = (number)(3.14159265358979323846 * freq / this->sr);
    number t = (number)(rnbo_sin(omega2) / rnbo_cos(omega2));
    array<number, 2> z0 = this->cross_tilde_04_complexDivide(1. - 0.5 * t, 0.866025403784 * t, 1. + 0.5 * t, -0.866025403784 * t);
    array<number, 2> z1 = {(1. - t) / (1. + t), 0.};
    array<number, 2> z2 = {z0[0], -z0[1]};
    number b0Coeff = (number)(z0[0] + z1[0] + z2[0]);
    number b1Coeff = (number)(z0[0] * z1[0] - z0[1] * z1[1] + (z0[0] * z2[0] - z0[1] * z2[1]));
    array<number, 2> n = this->cross_tilde_04_complexMultiply(z1[0], z1[1], z2[0], z2[1]);
    b1Coeff += n[0];
    array<number, 2> d = this->cross_tilde_04_complexMultiply(n[0], n[1], z0[0], z0[1]);
    number b2Coeff = (number)(d[0]);
    number oneOverA0 = (number)((1.0 - b0Coeff + b1Coeff - b2Coeff) / (number)8);
    number oneOverA1 = (number)((1.0 + b0Coeff + b1Coeff + b2Coeff) / (number)8);
    b1Coeff = 0 - b1Coeff;
    return {b0Coeff, b1Coeff, b2Coeff, oneOverA0, oneOverA1};
}

void cross_tilde_04_clear() {
    this->cross_tilde_04_x0 = 0;
    this->cross_tilde_04_x1 = 0;
    this->cross_tilde_04_x2 = 0;
    this->cross_tilde_04_x3 = 0;
    this->cross_tilde_04_y0L = 0;
    this->cross_tilde_04_y1L = 0;
    this->cross_tilde_04_y2L = 0;
    this->cross_tilde_04_y0H = 0;
    this->cross_tilde_04_y1H = 0;
    this->cross_tilde_04_y2H = 0;
}

void cross_tilde_04_reset() {
    this->cross_tilde_04_clear();
    this->cross_tilde_04_needsUpdate = true;
}

void cross_tilde_04_dspsetup(bool force) {
    if ((bool)(this->cross_tilde_04_setupDone) && (bool)(!(bool)(force)))
        return;

    this->cross_tilde_04_reset();
    this->cross_tilde_04_setupDone = true;
}

number gen_01_slide_3_next(number x, number up, number down) {
    number temp = x - this->gen_01_slide_3_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
    this->gen_01_slide_3_prev = this->gen_01_slide_3_prev + ((x > this->gen_01_slide_3_prev ? iup : idown)) * temp;
    return this->gen_01_slide_3_prev;
}

void gen_01_slide_3_reset() {
    this->gen_01_slide_3_prev = 0;
}

void phasor_03_onBeatTimeChanged(number beattime) {
    RNBO_UNUSED(beattime);
    this->phasor_03_recalcInc = true;
    this->phasor_03_recalcPhase = true;
}

number phasor_03_ph_next(number freq, number reset) {
    RNBO_UNUSED(reset);
    number pincr = freq * this->phasor_03_ph_conv;

    if (this->phasor_03_ph_currentPhase < 0.)
        this->phasor_03_ph_currentPhase = 1. + this->phasor_03_ph_currentPhase;

    if (this->phasor_03_ph_currentPhase > 1.)
        this->phasor_03_ph_currentPhase = this->phasor_03_ph_currentPhase - 1.;

    number tmp = this->phasor_03_ph_currentPhase;
    this->phasor_03_ph_currentPhase += pincr;
    return tmp;
}

void phasor_03_ph_reset() {
    this->phasor_03_ph_currentPhase = 0;
}

void phasor_03_ph_dspsetup() {
    this->phasor_03_ph_conv = (number)1 / this->sr;
}

void phasor_03_dspsetup(bool force) {
    if ((bool)(this->phasor_03_setupDone) && (bool)(!(bool)(force)))
        return;

    this->phasor_03_setupDone = true;
    this->phasor_03_ph_dspsetup();
}

number gen_02_slide_3_next(number x, number up, number down) {
    number temp = x - this->gen_02_slide_3_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
    this->gen_02_slide_3_prev = this->gen_02_slide_3_prev + ((x > this->gen_02_slide_3_prev ? iup : idown)) * temp;
    return this->gen_02_slide_3_prev;
}

void gen_02_slide_3_reset() {
    this->gen_02_slide_3_prev = 0;
}

number gen_03_slide_3_next(number x, number up, number down) {
    number temp = x - this->gen_03_slide_3_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
    this->gen_03_slide_3_prev = this->gen_03_slide_3_prev + ((x > this->gen_03_slide_3_prev ? iup : idown)) * temp;
    return this->gen_03_slide_3_prev;
}

void gen_03_slide_3_reset() {
    this->gen_03_slide_3_prev = 0;
}

void numberobj_03_init() {
    this->numberobj_03_currentFormat = 6;
}

void numberobj_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->numberobj_03_value;
}

void numberobj_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->numberobj_03_value_set(preset["value"]);
}

number gen_04_slide_3_next(number x, number up, number down) {
    number temp = x - this->gen_04_slide_3_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
    this->gen_04_slide_3_prev = this->gen_04_slide_3_prev + ((x > this->gen_04_slide_3_prev ? iup : idown)) * temp;
    return this->gen_04_slide_3_prev;
}

void gen_04_slide_3_reset() {
    this->gen_04_slide_3_prev = 0;
}

number gen_05_slide_3_next(number x, number up, number down) {
    number temp = x - this->gen_05_slide_3_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
    this->gen_05_slide_3_prev = this->gen_05_slide_3_prev + ((x > this->gen_05_slide_3_prev ? iup : idown)) * temp;
    return this->gen_05_slide_3_prev;
}

void gen_05_slide_3_reset() {
    this->gen_05_slide_3_prev = 0;
}

number gen_06_slide_3_next(number x, number up, number down) {
    number temp = x - this->gen_06_slide_3_prev;
    auto iup = this->safediv(1., this->maximum(1., rnbo_abs(up)));
    auto idown = this->safediv(1., this->maximum(1., rnbo_abs(down)));
    this->gen_06_slide_3_prev = this->gen_06_slide_3_prev + ((x > this->gen_06_slide_3_prev ? iup : idown)) * temp;
    return this->gen_06_slide_3_prev;
}

void gen_06_slide_3_reset() {
    this->gen_06_slide_3_prev = 0;
}

void param_01_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_01_value;
}

void param_01_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_01_value_set(preset["value"]);
}

void param_02_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_02_value;
}

void param_02_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_02_value_set(preset["value"]);
}

void param_03_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_03_value;
}

void param_03_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_03_value_set(preset["value"]);
}

void param_04_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_04_value;
}

void param_04_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_04_value_set(preset["value"]);
}

void param_05_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_05_value;
}

void param_05_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_05_value_set(preset["value"]);
}

void param_06_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_06_value;
}

void param_06_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_06_value_set(preset["value"]);
}

void param_07_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_07_value;
}

void param_07_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_07_value_set(preset["value"]);
}

void param_08_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_08_value;
}

void param_08_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_08_value_set(preset["value"]);
}

void param_09_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_09_value;
}

void param_09_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_09_value_set(preset["value"]);
}

void param_10_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_10_value;
}

void param_10_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_10_value_set(preset["value"]);
}

void param_11_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_11_value;
}

void param_11_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_11_value_set(preset["value"]);
}

void param_12_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_12_value;
}

void param_12_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_12_value_set(preset["value"]);
}

void param_13_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_13_value;
}

void param_13_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_13_value_set(preset["value"]);
}

void param_14_getPresetValue(PatcherStateInterface& preset) {
    preset["value"] = this->param_14_value;
}

void param_14_setPresetValue(PatcherStateInterface& preset) {
    if ((bool)(stateIsEmpty(preset)))
        return;

    this->param_14_value_set(preset["value"]);
}

number globaltransport_getSampleOffset(MillisecondTime time) {
    return this->mstosamps(this->maximum(0, time - this->getEngine()->getCurrentTime()));
}

number globaltransport_getTempoAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < (SampleIndex)(this->vs) ? this->globaltransport_tempo[(Index)sampleOffset] : this->globaltransport_lastTempo);
}

number globaltransport_getStateAtSample(SampleIndex sampleOffset) {
    return (sampleOffset >= 0 && sampleOffset < (SampleIndex)(this->vs) ? this->globaltransport_state[(Index)sampleOffset] : this->globaltransport_lastState);
}

number globaltransport_getState(MillisecondTime time) {
    return this->globaltransport_getStateAtSample((SampleIndex)(this->globaltransport_getSampleOffset(time)));
}

number globaltransport_getTempo(MillisecondTime time) {
    return this->globaltransport_getTempoAtSample((SampleIndex)(this->globaltransport_getSampleOffset(time)));
}

number globaltransport_getBeatTime(MillisecondTime time) {
    number i = 2;

    while (i < this->globaltransport_beatTimeChanges->length && this->globaltransport_beatTimeChanges[(Index)(i + 1)] <= time) {
        i += 2;
    }

    i -= 2;
    number beatTimeBase = this->globaltransport_beatTimeChanges[(Index)i];

    if (this->globaltransport_getState(time) == 0)
        return beatTimeBase;

    number beatTimeBaseMsTime = this->globaltransport_beatTimeChanges[(Index)(i + 1)];
    number diff = time - beatTimeBaseMsTime;
    number diffInBeats = diff * this->globaltransport_getTempo(time) * 0.008 / (number)480;
    return beatTimeBase + diffInBeats;
}

bool globaltransport_setTempo(MillisecondTime time, number tempo, bool notify) {
    if ((bool)(notify)) {
        this->processTempoEvent(time, tempo);
        this->globaltransport_notify = true;
    } else {
        Index offset = (Index)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getTempoAtSample((SampleIndex)(offset)) != tempo) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_tempo, this->vs, tempo, offset);
            this->globaltransport_lastTempo = tempo;
            this->globaltransport_tempoNeedsReset = true;
            return true;
        }
    }

    return false;
}

bool globaltransport_setState(MillisecondTime time, number state, bool notify) {
    if ((bool)(notify)) {
        this->processTransportEvent(time, TransportState(state));
        this->globaltransport_notify = true;
    } else {
        SampleIndex offset = (SampleIndex)(this->globaltransport_getSampleOffset(time));

        if (this->globaltransport_getStateAtSample(offset) != state) {
            this->globaltransport_beatTimeChanges->push(this->globaltransport_getBeatTime(time));
            this->globaltransport_beatTimeChanges->push(time);
            fillSignal(this->globaltransport_state, this->vs, state, (Index)(offset));
            this->globaltransport_lastState = TransportState(state);
            this->globaltransport_stateNeedsReset = true;
            return true;
        }
    }

    return false;
}

bool globaltransport_setBeatTime(MillisecondTime time, number beattime, bool notify) {
    if ((bool)(notify)) {
        this->processBeatTimeEvent(time, beattime);
        this->globaltransport_notify = true;
        return false;
    } else {
        bool beatTimeHasChanged = false;

        if (rnbo_abs(beattime - this->globaltransport_getBeatTime(time)) > 0.001) {
            beatTimeHasChanged = true;
        }

        this->globaltransport_beatTimeChanges->push(beattime);
        this->globaltransport_beatTimeChanges->push(time);
        return beatTimeHasChanged;
    }
}

number globaltransport_getBeatTimeAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBeatTime(this->getEngine()->getCurrentTime() + msOffset);
}

array<number, 2> globaltransport_getTimeSignature(MillisecondTime time) {
    number i = 3;

    while (i < this->globaltransport_timeSignatureChanges->length && this->globaltransport_timeSignatureChanges[(Index)(i + 2)] <= time) {
        i += 3;
    }

    i -= 3;

    return {
        this->globaltransport_timeSignatureChanges[(Index)i],
        this->globaltransport_timeSignatureChanges[(Index)(i + 1)]
    };
}

array<number, 2> globaltransport_getTimeSignatureAtSample(SampleIndex sampleOffset) {
    MillisecondTime msOffset = (MillisecondTime)(this->sampstoms(sampleOffset));
    return this->globaltransport_getTimeSignature(this->getEngine()->getCurrentTime() + msOffset);
}

void globaltransport_setBBUBase(
    MillisecondTime time,
    number numerator,
    number denominator,
    number bars,
    number beats,
    number units
) {
    number beatsInQuarterNotes = this->globaltransport_getBeatTime(time);
    bars--;
    beats--;
    number beatsIncCurrenttDenom = beatsInQuarterNotes * (denominator * 0.25);
    number beatLength = (number)4 / denominator;
    number beatLengthInUnits = beatLength * 480;

    while (units > beatLengthInUnits) {
        units -= beatLengthInUnits;
        beats++;
    }

    number targetBeatTime = bars * numerator + beats + units / beatLengthInUnits;
    this->globaltransport_bbuBase = targetBeatTime - beatsIncCurrenttDenom;
}

array<number, 3> globaltransport_getBBU(MillisecondTime time) {
    array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);
    number numerator = currentSig[0];
    number denominator = currentSig[1];
    number beatsInQuarterNotes = this->globaltransport_getBeatTime(time);
    number beatsIncCurrenttDenom = beatsInQuarterNotes * (denominator * 0.25);
    number beatLength = (number)4 / denominator;
    number beatLengthInUnits = beatLength * 480;
    number targetBeatTime = beatsIncCurrenttDenom + this->globaltransport_bbuBase;
    number currentBars = 0;
    number currentBeats = 0;
    number currentUnits = 0;

    if (targetBeatTime >= 0) {
        currentBars = trunc(targetBeatTime / numerator);
        targetBeatTime -= currentBars * numerator;
        currentBeats = trunc(targetBeatTime);
        targetBeatTime -= currentBeats;
        currentUnits = targetBeatTime * beatLengthInUnits;
    } else {
        currentBars = trunc(targetBeatTime / numerator);
        targetBeatTime -= currentBars * numerator;

        if (targetBeatTime != 0) {
            currentBars -= 1;
            currentBeats = trunc(targetBeatTime);
            targetBeatTime -= currentBeats;
            currentBeats = numerator + currentBeats;
            currentUnits = targetBeatTime * beatLengthInUnits;

            if (currentUnits != 0) {
                currentUnits = beatLengthInUnits + currentUnits;
                currentBeats -= 1;
            }
        }
    }

    return {currentBars + 1, currentBeats + 1, currentUnits};
}

bool globaltransport_setTimeSignature(MillisecondTime time, number numerator, number denominator, bool notify) {
    if ((bool)(notify)) {
        this->processTimeSignatureEvent(time, (Int)(numerator), (Int)(denominator));
        this->globaltransport_notify = true;
    } else {
        array<number, 2> currentSig = this->globaltransport_getTimeSignature(time);

        if (currentSig[0] != numerator || currentSig[1] != denominator) {
            array<number, 3> bbu = this->globaltransport_getBBU(time);
            this->globaltransport_setBBUBase(time, numerator, denominator, bbu[0], bbu[1], bbu[2]);
            this->globaltransport_timeSignatureChanges->push(numerator);
            this->globaltransport_timeSignatureChanges->push(denominator);
            this->globaltransport_timeSignatureChanges->push(time);
            return true;
        }
    }

    return false;
}

array<number, 3> globaltransport_getBBUAtSample(SampleIndex sampleOffset) {
    auto msOffset = this->sampstoms(sampleOffset);
    return this->globaltransport_getBBU(this->getEngine()->getCurrentTime() + msOffset);
}

bool globaltransport_setBBU(MillisecondTime time, number bars, number beats, number units, bool notify) {
    RNBO_UNUSED(notify);
    array<number, 2> sig = this->globaltransport_getTimeSignature(time);
    number numerator = sig[0];
    number denominator = sig[1];
    this->globaltransport_setBBUBase(time, numerator, denominator, bars, beats, units);
    return true;
}

void globaltransport_advance() {
    if ((bool)(this->globaltransport_tempoNeedsReset)) {
        fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
        this->globaltransport_tempoNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTempoEvent(this->globaltransport_lastTempo);
        }
    }

    if ((bool)(this->globaltransport_stateNeedsReset)) {
        fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
        this->globaltransport_stateNeedsReset = false;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTransportEvent(TransportState(this->globaltransport_lastState));
        }
    }

    if (this->globaltransport_beatTimeChanges->length > 2) {
        this->globaltransport_beatTimeChanges[0] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 2)];
        this->globaltransport_beatTimeChanges[1] = this->globaltransport_beatTimeChanges[(Index)(this->globaltransport_beatTimeChanges->length - 1)];
        this->globaltransport_beatTimeChanges->length = 2;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendBeatTimeEvent(this->globaltransport_beatTimeChanges[0]);
        }
    }

    if (this->globaltransport_timeSignatureChanges->length > 3) {
        this->globaltransport_timeSignatureChanges[0] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 3)];
        this->globaltransport_timeSignatureChanges[1] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 2)];
        this->globaltransport_timeSignatureChanges[2] = this->globaltransport_timeSignatureChanges[(Index)(this->globaltransport_timeSignatureChanges->length - 1)];
        this->globaltransport_timeSignatureChanges->length = 3;

        if ((bool)(this->globaltransport_notify)) {
            this->getEngine()->sendTimeSignatureEvent(
                (Int)(this->globaltransport_timeSignatureChanges[0]),
                (Int)(this->globaltransport_timeSignatureChanges[1])
            );
        }
    }

    this->globaltransport_notify = false;
}

void globaltransport_dspsetup(bool force) {
    if ((bool)(this->globaltransport_setupDone) && (bool)(!(bool)(force)))
        return;

    fillSignal(this->globaltransport_tempo, this->vs, this->globaltransport_lastTempo);
    this->globaltransport_tempoNeedsReset = false;
    fillSignal(this->globaltransport_state, this->vs, this->globaltransport_lastState);
    this->globaltransport_stateNeedsReset = false;
    this->globaltransport_setupDone = true;
}

bool stackprotect_check() {
    this->stackprotect_count++;

    if (this->stackprotect_count > 128) {
        console->log("STACK OVERFLOW DETECTED - stopped processing branch !");
        return true;
    }

    return false;
}

Index getPatcherSerial() const {
    return 0;
}

void sendParameter(ParameterIndex index, bool ignoreValue) {
    this->getEngine()->notifyParameterValueChanged(index, (ignoreValue ? 0 : this->getParameterValue(index)), ignoreValue);
}

void scheduleParamInit(ParameterIndex index, Index order) {
    this->paramInitIndices->push(index);
    this->paramInitOrder->push(order);
}

void processParamInitEvents() {
    this->listquicksort(
        this->paramInitOrder,
        this->paramInitIndices,
        0,
        (int)(this->paramInitOrder->length - 1),
        true
    );

    for (Index i = 0; i < this->paramInitOrder->length; i++) {
        this->getEngine()->scheduleParameterBang(this->paramInitIndices[i], 0);
    }
}

void updateTime(MillisecondTime time, EXTERNALENGINE* engine, bool inProcess = false) {
    RNBO_UNUSED(inProcess);
    RNBO_UNUSED(engine);
    this->_currentTime = time;
    auto offset = rnbo_fround(this->msToSamps(time - this->getEngine()->getCurrentTime(), this->sr));

    if (offset >= (SampleIndex)(this->vs))
        offset = (SampleIndex)(this->vs) - 1;

    if (offset < 0)
        offset = 0;

    this->sampleOffsetIntoNextAudioBuffer = (Index)(offset);
}

void assign_defaults()
{
    cross_tilde_01_x = 0;
    cross_tilde_01_freq = 1000;
    dspexpr_07_in1 = 0;
    dspexpr_07_in2 = 0;
    receive_05_output_number = 0;
    expr_09_in1 = 0;
    expr_09_in2 = 2;
    expr_09_out1 = 0;
    dspexpr_08_in1 = 0;
    dspexpr_08_in2 = 0;
    receive_06_output_number = 0;
    dspexpr_09_in1 = 0;
    dspexpr_09_in2 = 0;
    dspexpr_10_in1 = 0;
    dspexpr_10_in2 = 0;
    cross_tilde_02_x = 0;
    cross_tilde_02_freq = 1000;
    numberobj_01_value = 0;
    numberobj_01_value_setter(numberobj_01_value);
    dspexpr_11_in1 = 0;
    dspexpr_11_in2 = 0;
    selector_01_onoff = 1;
    dspexpr_12_in1 = 0;
    dspexpr_12_in2 = 0;
    dspexpr_13_in1 = 0;
    dspexpr_13_in2 = 0;
    phasor_01_freq = 0;
    receive_07_output_number = 0;
    receive_08_output_number = 0;
    expr_10_in1 = 0;
    expr_10_in2 = 2;
    expr_10_out1 = 0;
    codebox_tilde_04_in1 = 0;
    dspexpr_14_in1 = 0;
    dspexpr_14_in2 = 0;
    dspexpr_15_in1 = 0;
    dspexpr_15_in2 = 0;
    dspexpr_16_in1 = 0;
    dspexpr_16_in2 = 0;
    dspexpr_17_in1 = 0;
    dspexpr_17_in2 = 0;
    dspexpr_18_in1 = 0;
    dspexpr_18_in2 = 0;
    selector_02_onoff = 1;
    numberobj_02_value = 0;
    numberobj_02_value_setter(numberobj_02_value);
    dspexpr_19_in1 = 0;
    dspexpr_19_in2 = 0.5;
    receive_09_output_number = 0;
    cross_tilde_03_x = 0;
    cross_tilde_03_freq = 1000;
    phasor_02_freq = 0;
    dspexpr_20_in1 = 0;
    dspexpr_20_in2 = 0;
    cross_tilde_04_x = 0;
    cross_tilde_04_freq = 1000;
    receive_10_output_number = 0;
    expr_11_in1 = 0;
    expr_11_in2 = 2;
    expr_11_out1 = 0;
    selector_03_onoff = 1;
    dspexpr_21_in1 = 0;
    dspexpr_21_in2 = 0;
    dspexpr_22_in1 = 0;
    dspexpr_22_in2 = 0;
    gen_01_in1 = 0;
    gen_01_in2 = 0;
    gen_01_in3 = 0;
    gen_01_in4 = 0;
    gen_01_in5 = 0;
    phasor_03_freq = 0;
    gen_02_in1 = 0;
    gen_02_in2 = 0;
    gen_02_in3 = 0;
    gen_02_in4 = 0;
    gen_02_in5 = 0;
    gen_03_in1 = 0;
    gen_03_in2 = 0;
    gen_03_in3 = 0;
    gen_03_in4 = 0;
    gen_03_in5 = 0;
    dspexpr_23_in1 = 0;
    dspexpr_23_in2 = 0;
    numberobj_03_value = 0;
    numberobj_03_value_setter(numberobj_03_value);
    codebox_tilde_05_in1 = 0;
    codebox_tilde_05_in2 = 0;
    codebox_tilde_05_in3 = 0;
    codebox_tilde_05_in4 = 0;
    codebox_tilde_05_in5 = 0;
    codebox_tilde_05_in6 = 0;
    codebox_tilde_05_in7 = 0;
    codebox_tilde_05_in8 = 0;
    codebox_tilde_05_in9 = 0;
    codebox_tilde_05_in10 = 0;
    codebox_tilde_05_in11 = 0;
    codebox_tilde_05_in12 = 0;
    codebox_tilde_05_in13 = 0;
    codebox_tilde_05_in14 = 0;
    dspexpr_24_in1 = 0;
    dspexpr_24_in2 = 0;
    dspexpr_24_in3 = 0.95;
    dspexpr_25_in1 = 0;
    dspexpr_25_in2 = 0;
    dspexpr_26_in1 = 0;
    dspexpr_26_in2 = 0;
    dspexpr_27_in1 = 0;
    dspexpr_27_in2 = 0;
    dspexpr_28_in1 = 0;
    dspexpr_28_in2 = 0;
    dspexpr_28_in3 = 0.95;
    dspexpr_29_in1 = 0;
    dspexpr_29_in2 = 0;
    receive_11_output_number = 0;
    p_01_target = 0;
    expr_12_in1 = 0;
    expr_12_in2 = 0.2;
    expr_12_out1 = 0;
    dspexpr_30_in1 = 0;
    dspexpr_30_in2 = 0;
    dspexpr_30_in3 = 0.95;
    dspexpr_31_in1 = 0;
    dspexpr_31_in2 = 0;
    dspexpr_32_in1 = 0;
    dspexpr_32_in2 = 0;
    dspexpr_33_in1 = 0;
    dspexpr_33_in2 = 0;
    dspexpr_34_in1 = 0;
    dspexpr_34_in2 = 0;
    gen_04_in1 = 0;
    gen_04_in2 = 0;
    gen_04_in3 = 0;
    gen_04_in4 = 0;
    gen_04_in5 = 0;
    expr_13_in1 = 0;
    expr_13_in2 = 0.25;
    expr_13_out1 = 0;
    gen_05_in1 = 0;
    gen_05_in2 = 0;
    gen_05_in3 = 0;
    gen_05_in4 = 0;
    gen_05_in5 = 0;
    gen_06_in1 = 0;
    gen_06_in2 = 0;
    gen_06_in3 = 0;
    gen_06_in4 = 0;
    gen_06_in5 = 0;
    receive_12_output_number = 0;
    expr_14_in1 = 0;
    expr_14_in2 = 0.15;
    expr_14_out1 = 0;
    send_01_input_number = 0;
    send_02_input_number = 0;
    param_01_value = 0.5;
    param_02_value = 0.5;
    send_03_input_number = 0;
    boolnum_01_val = false;
    param_03_value = 1;
    param_04_value = 0.5;
    send_04_input_number = 0;
    param_05_value = 1;
    boolnum_02_val = false;
    expr_15_in1 = 0;
    expr_15_in2 = 1;
    expr_15_out1 = 0;
    send_05_input_number = 0;
    dspexpr_35_in1 = 0;
    dspexpr_35_in2 = 0;
    dspexpr_35_in3 = 0.95;
    dspexpr_36_in1 = 0;
    dspexpr_36_in2 = 0;
    dspexpr_37_in1 = 0;
    dspexpr_37_in2 = 0;
    send_06_input_number = 0;
    expr_16_in1 = 0;
    expr_16_in2 = 1;
    expr_16_out1 = 0;
    expr_17_in1 = 0;
    expr_17_in2 = 2;
    expr_17_out1 = 0;
    expr_18_in1 = 0;
    expr_18_out1 = 0;
    dspexpr_38_in1 = 0;
    dspexpr_38_in2 = 0;
    dspexpr_38_in3 = 0.95;
    dspexpr_39_in1 = 0;
    dspexpr_39_in2 = 0;
    dspexpr_40_in1 = 0;
    dspexpr_40_in2 = 0;
    send_07_input_number = 0;
    param_06_value = 0;
    send_08_input_number = 0;
    param_07_value = 0.5;
    param_08_value = 0.5;
    param_09_value = 0.5;
    param_10_value = 0.5;
    send_09_input_number = 0;
    send_10_input_number = 0;
    send_11_input_number = 0;
    dspexpr_41_in1 = 0;
    dspexpr_41_in2 = 0;
    dspexpr_41_in3 = 0.95;
    dspexpr_42_in1 = 0;
    dspexpr_42_in2 = 0;
    dspexpr_43_in1 = 0;
    dspexpr_43_in2 = 0;
    receive_13_output_number = 0;
    dspexpr_44_in1 = 0;
    dspexpr_44_in2 = 0.05;
    dspexpr_44_in3 = 0.95;
    dspexpr_45_in1 = 0;
    dspexpr_45_in2 = 0;
    expr_19_in1 = 0;
    expr_19_in2 = 0.18;
    expr_19_out1 = 0;
    send_12_input_number = 0;
    expr_20_in1 = 0;
    expr_20_in2 = 512;
    expr_20_out1 = 0;
    expr_21_in1 = 0;
    expr_21_in2 = 480;
    expr_21_out1 = 0;
    dspexpr_46_in1 = 0;
    dspexpr_46_in2 = 0.05;
    dspexpr_46_in3 = 0.95;
    dspexpr_47_in1 = 0;
    dspexpr_47_in2 = 0;
    expr_22_in1 = 0;
    expr_22_in2 = 0.2;
    expr_22_out1 = 0;
    receive_14_output_number = 0;
    send_13_input_number = 0;
    boolnum_03_val = false;
    param_11_value = 0;
    codebox_tilde_06_in1 = 0;
    codebox_tilde_06_in2 = 0;
    expr_23_in1 = 0;
    expr_23_in2 = 0;
    expr_23_in3 = 4000;
    expr_23_out1 = 0;
    param_12_value = 800;
    dspexpr_48_in1 = 0;
    dspexpr_48_in2 = 0.05;
    dspexpr_48_in3 = 0.95;
    dspexpr_49_in1 = 0;
    dspexpr_49_in2 = 0;
    expr_24_in1 = 0;
    expr_24_in2 = 0.12;
    expr_24_out1 = 0;
    expr_25_in1 = 0;
    expr_25_in2 = 0;
    expr_25_in3 = 8000;
    expr_25_out1 = 0;
    param_13_value = 2000;
    send_14_input_number = 0;
    param_14_value = 0.3;
    _currentTime = 0;
    audioProcessSampleCount = 0;
    sampleOffsetIntoNextAudioBuffer = 0;
    zeroBuffer = nullptr;
    dummyBuffer = nullptr;
    signals[0] = nullptr;
    signals[1] = nullptr;
    signals[2] = nullptr;
    signals[3] = nullptr;
    signals[4] = nullptr;
    signals[5] = nullptr;
    signals[6] = nullptr;
    signals[7] = nullptr;
    signals[8] = nullptr;
    signals[9] = nullptr;
    signals[10] = nullptr;
    signals[11] = nullptr;
    signals[12] = nullptr;
    signals[13] = nullptr;
    signals[14] = nullptr;
    signals[15] = nullptr;
    signals[16] = nullptr;
    signals[17] = nullptr;
    signals[18] = nullptr;
    signals[19] = nullptr;
    signals[20] = nullptr;
    signals[21] = nullptr;
    signals[22] = nullptr;
    signals[23] = nullptr;
    signals[24] = nullptr;
    signals[25] = nullptr;
    signals[26] = nullptr;
    didAllocateSignals = 0;
    vs = 0;
    maxvs = 0;
    sr = 44100;
    invsr = 0.000022675736961451248;
    cross_tilde_01_needsUpdate = false;
    cross_tilde_01__freq = 0;
    cross_tilde_01_x0 = 0;
    cross_tilde_01_x1 = 0;
    cross_tilde_01_x2 = 0;
    cross_tilde_01_x3 = 0;
    cross_tilde_01_y0L = 0;
    cross_tilde_01_y1L = 0;
    cross_tilde_01_y2L = 0;
    cross_tilde_01_y0H = 0;
    cross_tilde_01_y1H = 0;
    cross_tilde_01_y2H = 0;
    cross_tilde_01_b0 = 0;
    cross_tilde_01_b1 = 0;
    cross_tilde_01_b2 = 0;
    cross_tilde_01_oneOverA0 = 0;
    cross_tilde_01_oneOverA1 = 0;
    cross_tilde_01_setupDone = false;
    cross_tilde_02_needsUpdate = false;
    cross_tilde_02__freq = 0;
    cross_tilde_02_x0 = 0;
    cross_tilde_02_x1 = 0;
    cross_tilde_02_x2 = 0;
    cross_tilde_02_x3 = 0;
    cross_tilde_02_y0L = 0;
    cross_tilde_02_y1L = 0;
    cross_tilde_02_y2L = 0;
    cross_tilde_02_y0H = 0;
    cross_tilde_02_y1H = 0;
    cross_tilde_02_y2H = 0;
    cross_tilde_02_b0 = 0;
    cross_tilde_02_b1 = 0;
    cross_tilde_02_b2 = 0;
    cross_tilde_02_oneOverA0 = 0;
    cross_tilde_02_oneOverA1 = 0;
    cross_tilde_02_setupDone = false;
    numberobj_01_currentFormat = 6;
    numberobj_01_lastValue = 0;
    phasor_01_sigbuf = nullptr;
    phasor_01_lastLockedPhase = 0;
    phasor_01_lastQuantum = 0;
    phasor_01_lastTempo = 0;
    phasor_01_nextJumpInSamples = 0;
    phasor_01_inc = 0;
    phasor_01_recalcInc = true;
    phasor_01_recalcPhase = true;
    phasor_01_ph_currentPhase = 0;
    phasor_01_ph_conv = 0;
    phasor_01_setupDone = false;
    numberobj_02_currentFormat = 6;
    numberobj_02_lastValue = 0;
    cross_tilde_03_needsUpdate = false;
    cross_tilde_03__freq = 0;
    cross_tilde_03_x0 = 0;
    cross_tilde_03_x1 = 0;
    cross_tilde_03_x2 = 0;
    cross_tilde_03_x3 = 0;
    cross_tilde_03_y0L = 0;
    cross_tilde_03_y1L = 0;
    cross_tilde_03_y2L = 0;
    cross_tilde_03_y0H = 0;
    cross_tilde_03_y1H = 0;
    cross_tilde_03_y2H = 0;
    cross_tilde_03_b0 = 0;
    cross_tilde_03_b1 = 0;
    cross_tilde_03_b2 = 0;
    cross_tilde_03_oneOverA0 = 0;
    cross_tilde_03_oneOverA1 = 0;
    cross_tilde_03_setupDone = false;
    phasor_02_sigbuf = nullptr;
    phasor_02_lastLockedPhase = 0;
    phasor_02_lastQuantum = 0;
    phasor_02_lastTempo = 0;
    phasor_02_nextJumpInSamples = 0;
    phasor_02_inc = 0;
    phasor_02_recalcInc = true;
    phasor_02_recalcPhase = true;
    phasor_02_ph_currentPhase = 0;
    phasor_02_ph_conv = 0;
    phasor_02_setupDone = false;
    cross_tilde_04_needsUpdate = false;
    cross_tilde_04__freq = 0;
    cross_tilde_04_x0 = 0;
    cross_tilde_04_x1 = 0;
    cross_tilde_04_x2 = 0;
    cross_tilde_04_x3 = 0;
    cross_tilde_04_y0L = 0;
    cross_tilde_04_y1L = 0;
    cross_tilde_04_y2L = 0;
    cross_tilde_04_y0H = 0;
    cross_tilde_04_y1H = 0;
    cross_tilde_04_y2H = 0;
    cross_tilde_04_b0 = 0;
    cross_tilde_04_b1 = 0;
    cross_tilde_04_b2 = 0;
    cross_tilde_04_oneOverA0 = 0;
    cross_tilde_04_oneOverA1 = 0;
    cross_tilde_04_setupDone = false;
    gen_01_slide_3_prev = 0;
    phasor_03_sigbuf = nullptr;
    phasor_03_lastLockedPhase = 0;
    phasor_03_lastQuantum = 0;
    phasor_03_lastTempo = 0;
    phasor_03_nextJumpInSamples = 0;
    phasor_03_inc = 0;
    phasor_03_recalcInc = true;
    phasor_03_recalcPhase = true;
    phasor_03_ph_currentPhase = 0;
    phasor_03_ph_conv = 0;
    phasor_03_setupDone = false;
    gen_02_slide_3_prev = 0;
    gen_03_slide_3_prev = 0;
    numberobj_03_currentFormat = 6;
    numberobj_03_lastValue = 0;
    gen_04_slide_3_prev = 0;
    gen_05_slide_3_prev = 0;
    gen_06_slide_3_prev = 0;
    param_01_lastValue = 0;
    param_02_lastValue = 0;
    param_03_lastValue = 0;
    param_04_lastValue = 0;
    param_05_lastValue = 0;
    param_06_lastValue = 0;
    param_07_lastValue = 0;
    param_08_lastValue = 0;
    param_09_lastValue = 0;
    param_10_lastValue = 0;
    param_11_lastValue = 0;
    param_12_lastValue = 0;
    param_13_lastValue = 0;
    param_14_lastValue = 0;
    globaltransport_tempo = nullptr;
    globaltransport_tempoNeedsReset = false;
    globaltransport_lastTempo = 120;
    globaltransport_state = nullptr;
    globaltransport_stateNeedsReset = false;
    globaltransport_lastState = 0;
    globaltransport_beatTimeChanges = { 0, 0 };
    globaltransport_timeSignatureChanges = { 4, 4, 0 };
    globaltransport_notify = false;
    globaltransport_bbuBase = 0;
    globaltransport_setupDone = false;
    stackprotect_count = 0;
    _voiceIndex = 0;
    _noteNumber = 0;
    isMuted = 1;
}

// member variables

    number cross_tilde_01_x;
    number cross_tilde_01_freq;
    number dspexpr_07_in1;
    number dspexpr_07_in2;
    number receive_05_output_number;
    list receive_05_output_list;
    number expr_09_in1;
    number expr_09_in2;
    number expr_09_out1;
    number dspexpr_08_in1;
    number dspexpr_08_in2;
    number receive_06_output_number;
    list receive_06_output_list;
    number dspexpr_09_in1;
    number dspexpr_09_in2;
    number dspexpr_10_in1;
    number dspexpr_10_in2;
    number cross_tilde_02_x;
    number cross_tilde_02_freq;
    number numberobj_01_value;
    number dspexpr_11_in1;
    number dspexpr_11_in2;
    number selector_01_onoff;
    number dspexpr_12_in1;
    number dspexpr_12_in2;
    number dspexpr_13_in1;
    number dspexpr_13_in2;
    number phasor_01_freq;
    number receive_07_output_number;
    list receive_07_output_list;
    number receive_08_output_number;
    list receive_08_output_list;
    number expr_10_in1;
    number expr_10_in2;
    number expr_10_out1;
    number codebox_tilde_04_in1;
    number dspexpr_14_in1;
    number dspexpr_14_in2;
    number dspexpr_15_in1;
    number dspexpr_15_in2;
    number dspexpr_16_in1;
    number dspexpr_16_in2;
    number dspexpr_17_in1;
    number dspexpr_17_in2;
    number dspexpr_18_in1;
    number dspexpr_18_in2;
    number selector_02_onoff;
    number numberobj_02_value;
    number dspexpr_19_in1;
    number dspexpr_19_in2;
    number receive_09_output_number;
    list receive_09_output_list;
    number cross_tilde_03_x;
    number cross_tilde_03_freq;
    number phasor_02_freq;
    number dspexpr_20_in1;
    number dspexpr_20_in2;
    number cross_tilde_04_x;
    number cross_tilde_04_freq;
    number receive_10_output_number;
    list receive_10_output_list;
    number expr_11_in1;
    number expr_11_in2;
    number expr_11_out1;
    number selector_03_onoff;
    number dspexpr_21_in1;
    number dspexpr_21_in2;
    number dspexpr_22_in1;
    number dspexpr_22_in2;
    number gen_01_in1;
    number gen_01_in2;
    number gen_01_in3;
    number gen_01_in4;
    number gen_01_in5;
    number phasor_03_freq;
    number gen_02_in1;
    number gen_02_in2;
    number gen_02_in3;
    number gen_02_in4;
    number gen_02_in5;
    number gen_03_in1;
    number gen_03_in2;
    number gen_03_in3;
    number gen_03_in4;
    number gen_03_in5;
    number dspexpr_23_in1;
    number dspexpr_23_in2;
    number numberobj_03_value;
    number codebox_tilde_05_in1;
    number codebox_tilde_05_in2;
    number codebox_tilde_05_in3;
    number codebox_tilde_05_in4;
    number codebox_tilde_05_in5;
    number codebox_tilde_05_in6;
    number codebox_tilde_05_in7;
    number codebox_tilde_05_in8;
    number codebox_tilde_05_in9;
    number codebox_tilde_05_in10;
    number codebox_tilde_05_in11;
    number codebox_tilde_05_in12;
    number codebox_tilde_05_in13;
    number codebox_tilde_05_in14;
    number dspexpr_24_in1;
    number dspexpr_24_in2;
    number dspexpr_24_in3;
    number dspexpr_25_in1;
    number dspexpr_25_in2;
    number dspexpr_26_in1;
    number dspexpr_26_in2;
    number dspexpr_27_in1;
    number dspexpr_27_in2;
    number dspexpr_28_in1;
    number dspexpr_28_in2;
    number dspexpr_28_in3;
    number dspexpr_29_in1;
    number dspexpr_29_in2;
    number receive_11_output_number;
    list receive_11_output_list;
    number p_01_target;
    number expr_12_in1;
    number expr_12_in2;
    number expr_12_out1;
    number dspexpr_30_in1;
    number dspexpr_30_in2;
    number dspexpr_30_in3;
    number dspexpr_31_in1;
    number dspexpr_31_in2;
    number dspexpr_32_in1;
    number dspexpr_32_in2;
    number dspexpr_33_in1;
    number dspexpr_33_in2;
    number dspexpr_34_in1;
    number dspexpr_34_in2;
    number gen_04_in1;
    number gen_04_in2;
    number gen_04_in3;
    number gen_04_in4;
    number gen_04_in5;
    number expr_13_in1;
    number expr_13_in2;
    number expr_13_out1;
    number gen_05_in1;
    number gen_05_in2;
    number gen_05_in3;
    number gen_05_in4;
    number gen_05_in5;
    number gen_06_in1;
    number gen_06_in2;
    number gen_06_in3;
    number gen_06_in4;
    number gen_06_in5;
    number receive_12_output_number;
    list receive_12_output_list;
    number expr_14_in1;
    number expr_14_in2;
    number expr_14_out1;
    number send_01_input_number;
    list send_01_input_list;
    number send_02_input_number;
    list send_02_input_list;
    number param_01_value;
    number param_02_value;
    number send_03_input_number;
    list send_03_input_list;
    number boolnum_01_val;
    number param_03_value;
    number param_04_value;
    number send_04_input_number;
    list send_04_input_list;
    number param_05_value;
    number boolnum_02_val;
    number expr_15_in1;
    number expr_15_in2;
    number expr_15_out1;
    number send_05_input_number;
    list send_05_input_list;
    number dspexpr_35_in1;
    number dspexpr_35_in2;
    number dspexpr_35_in3;
    number dspexpr_36_in1;
    number dspexpr_36_in2;
    number dspexpr_37_in1;
    number dspexpr_37_in2;
    number send_06_input_number;
    list send_06_input_list;
    number expr_16_in1;
    number expr_16_in2;
    number expr_16_out1;
    number expr_17_in1;
    number expr_17_in2;
    number expr_17_out1;
    number expr_18_in1;
    number expr_18_out1;
    number dspexpr_38_in1;
    number dspexpr_38_in2;
    number dspexpr_38_in3;
    number dspexpr_39_in1;
    number dspexpr_39_in2;
    number dspexpr_40_in1;
    number dspexpr_40_in2;
    number send_07_input_number;
    list send_07_input_list;
    number param_06_value;
    number send_08_input_number;
    list send_08_input_list;
    number param_07_value;
    number param_08_value;
    number param_09_value;
    number param_10_value;
    number send_09_input_number;
    list send_09_input_list;
    number send_10_input_number;
    list send_10_input_list;
    number send_11_input_number;
    list send_11_input_list;
    number dspexpr_41_in1;
    number dspexpr_41_in2;
    number dspexpr_41_in3;
    number dspexpr_42_in1;
    number dspexpr_42_in2;
    number dspexpr_43_in1;
    number dspexpr_43_in2;
    number receive_13_output_number;
    list receive_13_output_list;
    number dspexpr_44_in1;
    number dspexpr_44_in2;
    number dspexpr_44_in3;
    number dspexpr_45_in1;
    number dspexpr_45_in2;
    number expr_19_in1;
    number expr_19_in2;
    number expr_19_out1;
    number send_12_input_number;
    list send_12_input_list;
    number expr_20_in1;
    number expr_20_in2;
    number expr_20_out1;
    number expr_21_in1;
    number expr_21_in2;
    number expr_21_out1;
    number dspexpr_46_in1;
    number dspexpr_46_in2;
    number dspexpr_46_in3;
    number dspexpr_47_in1;
    number dspexpr_47_in2;
    number expr_22_in1;
    number expr_22_in2;
    number expr_22_out1;
    number receive_14_output_number;
    list receive_14_output_list;
    number send_13_input_number;
    list send_13_input_list;
    number boolnum_03_val;
    number param_11_value;
    number codebox_tilde_06_in1;
    number codebox_tilde_06_in2;
    number expr_23_in1;
    number expr_23_in2;
    number expr_23_in3;
    number expr_23_out1;
    number param_12_value;
    number dspexpr_48_in1;
    number dspexpr_48_in2;
    number dspexpr_48_in3;
    number dspexpr_49_in1;
    number dspexpr_49_in2;
    number expr_24_in1;
    number expr_24_in2;
    number expr_24_out1;
    number expr_25_in1;
    number expr_25_in2;
    number expr_25_in3;
    number expr_25_out1;
    number param_13_value;
    number send_14_input_number;
    list send_14_input_list;
    number param_14_value;
    MillisecondTime _currentTime;
    ENGINE _internalEngine;
    UInt64 audioProcessSampleCount;
    Index sampleOffsetIntoNextAudioBuffer;
    signal zeroBuffer;
    signal dummyBuffer;
    SampleValue * signals[27];
    bool didAllocateSignals;
    Index vs;
    Index maxvs;
    number sr;
    number invsr;
    bool cross_tilde_01_needsUpdate;
    number cross_tilde_01__freq;
    number cross_tilde_01_x0;
    number cross_tilde_01_x1;
    number cross_tilde_01_x2;
    number cross_tilde_01_x3;
    number cross_tilde_01_y0L;
    number cross_tilde_01_y1L;
    number cross_tilde_01_y2L;
    number cross_tilde_01_y0H;
    number cross_tilde_01_y1H;
    number cross_tilde_01_y2H;
    number cross_tilde_01_b0;
    number cross_tilde_01_b1;
    number cross_tilde_01_b2;
    number cross_tilde_01_oneOverA0;
    number cross_tilde_01_oneOverA1;
    bool cross_tilde_01_setupDone;
    bool cross_tilde_02_needsUpdate;
    number cross_tilde_02__freq;
    number cross_tilde_02_x0;
    number cross_tilde_02_x1;
    number cross_tilde_02_x2;
    number cross_tilde_02_x3;
    number cross_tilde_02_y0L;
    number cross_tilde_02_y1L;
    number cross_tilde_02_y2L;
    number cross_tilde_02_y0H;
    number cross_tilde_02_y1H;
    number cross_tilde_02_y2H;
    number cross_tilde_02_b0;
    number cross_tilde_02_b1;
    number cross_tilde_02_b2;
    number cross_tilde_02_oneOverA0;
    number cross_tilde_02_oneOverA1;
    bool cross_tilde_02_setupDone;
    Int numberobj_01_currentFormat;
    number numberobj_01_lastValue;
    signal phasor_01_sigbuf;
    number phasor_01_lastLockedPhase;
    number phasor_01_lastQuantum;
    number phasor_01_lastTempo;
    number phasor_01_nextJumpInSamples;
    number phasor_01_inc;
    bool phasor_01_recalcInc;
    bool phasor_01_recalcPhase;
    number phasor_01_ph_currentPhase;
    number phasor_01_ph_conv;
    bool phasor_01_setupDone;
    Int numberobj_02_currentFormat;
    number numberobj_02_lastValue;
    bool cross_tilde_03_needsUpdate;
    number cross_tilde_03__freq;
    number cross_tilde_03_x0;
    number cross_tilde_03_x1;
    number cross_tilde_03_x2;
    number cross_tilde_03_x3;
    number cross_tilde_03_y0L;
    number cross_tilde_03_y1L;
    number cross_tilde_03_y2L;
    number cross_tilde_03_y0H;
    number cross_tilde_03_y1H;
    number cross_tilde_03_y2H;
    number cross_tilde_03_b0;
    number cross_tilde_03_b1;
    number cross_tilde_03_b2;
    number cross_tilde_03_oneOverA0;
    number cross_tilde_03_oneOverA1;
    bool cross_tilde_03_setupDone;
    signal phasor_02_sigbuf;
    number phasor_02_lastLockedPhase;
    number phasor_02_lastQuantum;
    number phasor_02_lastTempo;
    number phasor_02_nextJumpInSamples;
    number phasor_02_inc;
    bool phasor_02_recalcInc;
    bool phasor_02_recalcPhase;
    number phasor_02_ph_currentPhase;
    number phasor_02_ph_conv;
    bool phasor_02_setupDone;
    bool cross_tilde_04_needsUpdate;
    number cross_tilde_04__freq;
    number cross_tilde_04_x0;
    number cross_tilde_04_x1;
    number cross_tilde_04_x2;
    number cross_tilde_04_x3;
    number cross_tilde_04_y0L;
    number cross_tilde_04_y1L;
    number cross_tilde_04_y2L;
    number cross_tilde_04_y0H;
    number cross_tilde_04_y1H;
    number cross_tilde_04_y2H;
    number cross_tilde_04_b0;
    number cross_tilde_04_b1;
    number cross_tilde_04_b2;
    number cross_tilde_04_oneOverA0;
    number cross_tilde_04_oneOverA1;
    bool cross_tilde_04_setupDone;
    number gen_01_slide_3_prev;
    signal phasor_03_sigbuf;
    number phasor_03_lastLockedPhase;
    number phasor_03_lastQuantum;
    number phasor_03_lastTempo;
    number phasor_03_nextJumpInSamples;
    number phasor_03_inc;
    bool phasor_03_recalcInc;
    bool phasor_03_recalcPhase;
    number phasor_03_ph_currentPhase;
    number phasor_03_ph_conv;
    bool phasor_03_setupDone;
    number gen_02_slide_3_prev;
    number gen_03_slide_3_prev;
    Int numberobj_03_currentFormat;
    number numberobj_03_lastValue;
    number gen_04_slide_3_prev;
    number gen_05_slide_3_prev;
    number gen_06_slide_3_prev;
    number param_01_lastValue;
    number param_02_lastValue;
    number param_03_lastValue;
    number param_04_lastValue;
    number param_05_lastValue;
    number param_06_lastValue;
    number param_07_lastValue;
    number param_08_lastValue;
    number param_09_lastValue;
    number param_10_lastValue;
    number param_11_lastValue;
    number param_12_lastValue;
    number param_13_lastValue;
    number param_14_lastValue;
    signal globaltransport_tempo;
    bool globaltransport_tempoNeedsReset;
    number globaltransport_lastTempo;
    signal globaltransport_state;
    bool globaltransport_stateNeedsReset;
    number globaltransport_lastState;
    list globaltransport_beatTimeChanges;
    list globaltransport_timeSignatureChanges;
    bool globaltransport_notify;
    number globaltransport_bbuBase;
    bool globaltransport_setupDone;
    number stackprotect_count;
    Index _voiceIndex;
    Int _noteNumber;
    Index isMuted;
    indexlist paramInitIndices;
    indexlist paramInitOrder;
    RNBOSubpatcher_60 p_01;
    bool _isInitialized = false;
};

static PatcherInterface* creaternbomatic()
{
    return new rnbomatic<EXTERNALENGINE>();
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" PatcherFactoryFunctionPtr GetPatcherFactoryFunction()
#else
extern "C" PatcherFactoryFunctionPtr rnbomaticFactoryFunction()
#endif
{
    return creaternbomatic;
}

#ifndef RNBO_NO_PATCHERFACTORY
extern "C" void SetLogger(Logger* logger)
#else
void rnbomaticSetLogger(Logger* logger)
#endif
{
    console = logger;
}

} // end RNBO namespace

