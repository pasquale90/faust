#if defined(_WIN32) || defined(_WIN64)
    #define DSP_API __declspec(dllexport)
#else
    #define DSP_API __attribute__((visibility("default")))
#endif

#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/meta.h>

<<includeIntrinsic>>
<<includeclass>>

static mydsp m_dsp;
static MapUI map_ui;

extern "C" {

    DSP_API void initDSP(int sampleRate) {
        m_dsp.init(sampleRate);
        m_dsp.buildUserInterface(&map_ui);
    }

    // template <typename T> // for the shake of proper usage and to supress a probable warning --> discarded to export functions for implementing the Integrated Faust interpreter.
    DSP_API void setParameter(const char* name, FAUSTFLOAT value) {
        map_ui.setParamValue(std::string(name), value); 
    }

    DSP_API FAUSTFLOAT getParameter(const char* name) { // Not used. Added for potential future debugging of the parameter's integration
        return map_ui.getParamValue(std::string(name)); 
    }

    DSP_API mydsp* getDSP() {
        return &m_dsp;
    }

    DSP_API MapUI* getMapUI() {
        return &map_ui;
    }

}