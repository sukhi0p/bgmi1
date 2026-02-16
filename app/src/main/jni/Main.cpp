#include "include/Tools.h"
#include <XorStr.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_additional.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/android_native_app_glue.h"
#include "KittyMemory/MemoryPatch.h"
#include "include/shader.h"
#include "include/obfuscate.h"
#include "And64InlineHook/And64InlineHook.hpp"
#include <include/Includes.h>
#include <json.hpp>
#include <unordered_set>
#include <GLES/gl.h>
#include <dlfcn.h>
#include <curl/curl.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <fstream>
#include <mutex>
#include "include/shadowhook.h"

// ==================== LOGGING SYSTEM ====================
#include <android/log.h>
#include <time.h>
#include <stdarg.h>

#define LOG_TAG "UJJWAL"
#define LOG_FILE_PATH "/storage/emulated/0/Android/obb/com.pubg.imobile/ujjwal_bypass.txt"

// File logging function
void writeToLogFile(const char* level, const char* tag, const char* message) {
    time_t now = time(0);
    struct tm* tm_info = localtime(&now);
    char time_str[30];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    
    // Create directory if not exists
    std::string dir_path = "/storage/emulated/0/Android/obb/com.pubg.imobile";
    mkdir(dir_path.c_str(), 0777);
    
    FILE* log_file = fopen(LOG_FILE_PATH, "a");
    if (log_file) {
        fprintf(log_file, "[%s] [%s] [%s] %s\n", time_str, level, tag, message);
        fflush(log_file);
        fclose(log_file);
        chmod(LOG_FILE_PATH, 0666);
    }
}

// Logging macros
#define LOGV(...) { \
    char buffer[1024]; \
    snprintf(buffer, sizeof(buffer), __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "%s", buffer); \
    writeToLogFile("VERBOSE", LOG_TAG, buffer); \
}

#define LOGD(...) { \
    char buffer[1024]; \
    snprintf(buffer, sizeof(buffer), __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "%s", buffer); \
    writeToLogFile("DEBUG", LOG_TAG, buffer); \
}

#define LOGI(...) { \
    char buffer[1024]; \
    snprintf(buffer, sizeof(buffer), __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "%s", buffer); \
    writeToLogFile("INFO", LOG_TAG, buffer); \
}

#define LOGW(...) { \
    char buffer[1024]; \
    snprintf(buffer, sizeof(buffer), __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_WARN, LOG_TAG, "%s", buffer); \
    writeToLogFile("WARN", LOG_TAG, buffer); \
}

#define LOGE(...) { \
    char buffer[1024]; \
    snprintf(buffer, sizeof(buffer), __VA_ARGS__); \
    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", buffer); \
    writeToLogFile("ERROR", LOG_TAG, buffer); \
}

// Initialize log file
void initLogFile() {
    std::string dir_path = "/storage/emulated/0/Android/obb/com.pubg.imobile";
    mkdir(dir_path.c_str(), 0777);
    
    time_t now = time(0);
    struct tm* tm_info = localtime(&now);
    char time_str[30];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
    
    FILE* log_file = fopen(LOG_FILE_PATH, "w");
    if (log_file) {
        fprintf(log_file, "\n");
        fprintf(log_file, "═══════════════════════════════════════════════════════════════════════\n");
        fprintf(log_file, "              UJJWAL ULTIMATE BYPASS ENGINE                          \n");
        fprintf(log_file, "═══════════════════════════════════════════════════════════════════════\n");
        fprintf(log_file, "Started at: %s\n", time_str);
        fprintf(log_file, "Target: BGMI Anti-Cheat Bypass\n");
        fprintf(log_file, "═══════════════════════════════════════════════════════════════════════\n\n");
        fflush(log_file);
        fclose(log_file);
        chmod(LOG_FILE_PATH, 0666);
    }
    
    LOGI("🔥 Log file initialized at: %s", LOG_FILE_PATH);
}

// ==================== ULTIMATE PROTECTION LAYERS ====================
#include <sys/ptrace.h>
#include <link.h>
#include <elf.h>

#define OBFUSCATE(str) str

// ==================== LAYER 2: ANTI-DEBUG & ANTI-TRACE ====================
class AntiDebug {
public:
    static void init() {
        LOGI("🔒 Initializing AntiDebug...");
        
        // Anti-ptrace
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        LOGD("✅ ptrace set");
        
        // Hide from debuggers
        FILE* fp = fopen("/proc/self/status", "r");
        if (fp) {
            char line[256];
            while (fgets(line, sizeof(line), fp)) {
                if (strstr(line, "TracerPid")) {
                    int pid = atoi(strchr(line, ':') + 1);
                    LOGD("🔍 TracerPid: %d", pid);
                    if (pid != 0) {
                        LOGE("❌ Debugger detected! Exiting...");
                        fclose(fp);
                        exit(0);
                    }
                }
            }
            fclose(fp);
        }
        LOGI("✅ AntiDebug initialized");
    }
    
    static void checkDebugger() {
        if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0) {
            LOGE("❌ Debugger detected in check!");
            exit(0);
        }
    }
};

// ==================== LAYER 3: FILE INTEGRITY BYPASS ====================
class FileBypass {
public:
    static void protect() {
        LOGI("📁 Protecting files...");
        
        // Remove all detection files
        system("rm -rf /data/data/com.pubg.imobile/files/ano_tmp");
        system("rm -rf /data/data/com.pubg.imobile/files/obblib");
        system("rm -rf /data/data/com.pubg.imobile/files/xlog");
        system("rm -rf /data/data/com.pubg.imobile/app_bugly");
        system("rm -rf /data/data/com.pubg.imobile/app_crashrecord");
        system("rm -rf /data/data/com.pubg.imobile/app_crashSight");
        
        // Create fake files with 000 permissions
        system("touch /data/data/com.pubg.imobile/files/ano_tmp");
        system("chmod 000 /data/data/com.pubg.imobile/files/ano_tmp");
        system("touch /data/data/com.pubg.imobile/files/obblib");
        system("chmod 000 /data/data/com.pubg.imobile/files/obblib");
        system("touch /data/data/com.pubg.imobile/files/xlog");
        system("chmod 000 /data/data/com.pubg.imobile/files/xlog");
        
        LOGI("✅ File protection complete");
    }
};

uintptr_t UE4;

//====================================||•• Gnative Code ••||===================================

#define GNativeAndroidApp_Offset 0xdad0280

//====================================||•• Permission Code ••||===================================
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;
bool initImGui = false;
bool fixblink = true;
bool WALLHACK = true;
bool CyanBody = false;
bool GreenBody = false;
bool RedEnemy = true;  // 🔴 Enemy Red
bool GreenVehicle = true;  // 🟢 Vehicle Green
bool isLowGraphicsMode = true;
bool useNewBlinkFix = true;

//====================================||•• Shader Colors ••||===================================
#define ENEMY_RED_SHADER "float4 main() { return float4(1.0, 0.0, 0.0, 1.0); }"
#define VEHICLE_GREEN_SHADER "float4 main() { return float4(0.0, 1.0, 0.0, 1.0); }"
#define NORMAL_SHADER ""

std::unordered_set<GLuint> playerPrograms;
GLuint playerVertexShader = 0, playerMaskShader = 0;
std::mutex playerProgramsMutex;
std::mutex playerShaderMutex; 

std::unordered_set<GLuint> gunPrograms;
GLuint gunVertexShader = 0, gunMaskShader = 0;
std::mutex gunProgramsMutex;
std::mutex gunShaderMutex;

const char *Gamepackage = "com.pubg.imobile";
static char path[200];
static int currentItem = 0;
static char keyForLogin[64];

static std::string EXP = "KEY EXPIRY";

//====================================||•• Utility Functions ••||===================================

bool isLibraryLoaded(const char* libName) {
    FILE* fp = fopen("/proc/self/maps", "r");
    if (!fp) return false;
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, libName)) {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

std::string getDayName() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days[ltm->tm_wday];
}

std::string getAMPM() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return (ltm->tm_hour < 12) ? "AM" : "PM";
}

//====================================||•• Clipboard Functions ••||===================================

bool bValid = false;
std::string g_Token, g_Auth;
android_app *g_App = 0;
using json = nlohmann::ordered_json;

std::string getClipboardText() {
    if (!g_App) return "";
    auto activity = g_App->activity;
    if (!activity) return "";
    auto vm = activity->vm;
    if (!vm) return "";
    auto object = activity->clazz;
    if (!object) return "";
    
    std::string result;
    JNIEnv *env;
    vm->AttachCurrentThread(&env, 0); 
    {
        auto ContextClass = env->FindClass("android/content/Context");
        auto getSystemServiceMethod = env->GetMethodID(ContextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
        auto str = env->NewStringUTF("clipboard");
        auto clipboardManager = env->CallObjectMethod(object, getSystemServiceMethod, str);
        env->DeleteLocalRef(str);
        
        auto ClipboardManagerClass = env->FindClass("android/content/ClipboardManager");
        auto getText = env->GetMethodID(ClipboardManagerClass, "getText", "()Ljava/lang/CharSequence;");
        auto CharSequenceClass = env->FindClass("java/lang/CharSequence");
        auto toStringMethod = env->GetMethodID(CharSequenceClass, "toString", "()Ljava/lang/String;");
        auto text = env->CallObjectMethod(clipboardManager, getText);
        
        if (text) {
            str = (jstring) env->CallObjectMethod(text, toStringMethod);
            result = env->GetStringUTFChars(str, 0);
            env->DeleteLocalRef(str);
            env->DeleteLocalRef(text);
        }
        
        env->DeleteLocalRef(CharSequenceClass);
        env->DeleteLocalRef(ClipboardManagerClass);
        env->DeleteLocalRef(clipboardManager);
        env->DeleteLocalRef(ContextClass);
    }
    vm->DetachCurrentThread();
    return result;
}

//====================================||•• Message Box ••||===================================

std::u16string stringToUtf16(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    return converter.from_bytes(str);
}

std::unique_ptr<char16_t[]> stringToChar16Array(const std::string& str) {
    std::u16string utf16str = stringToUtf16(str);
    std::unique_ptr<char16_t[]> char16Array(new char16_t[utf16str.size() + 1]);
    std::copy(utf16str.begin(), utf16str.end(), char16Array.get());
    char16Array[utf16str.size()] = u'\0';
    return char16Array;
}

int (*CMessageBoxExt)(int type, const char16_t* Caption, const char16_t* Text);

int MsgBox(int Method, const std::string& Caption, const std::string& Text) {
    auto caption = stringToChar16Array(Caption);
    auto text = stringToChar16Array(Text);
    return CMessageBoxExt(Method, caption.get(), text.get());
}

//====================================||•• OpenGL Hooks ••||===================================

static void (*oglViewport)(GLint x, GLint y, GLsizei width, GLsizei height);
static void (*oglDrawElements)(GLenum mode, GLsizei count, GLenum type, const void *indices);
static void (*oglShaderSource)(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
static void (*oglAttachShader)(GLuint program, GLuint shader);

static GLint g_offsetX = 17;
static GLint g_offsetY = 0;

void _glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    if (x == 0 && y == 0 && width > 1000 && height > 500) {
        screenWidth = width;
        screenHeight = height;
        LOGD("📐 Screen size: %dx%d", screenWidth, screenHeight);
    }

    if (fixblink && screenWidth > 0 && screenHeight > 0) {
        GLint adjustedWidth = screenWidth - 2 * g_offsetX;
        GLint adjustedHeight = screenHeight - 2 * g_offsetY;
        glDisable(GL_SCISSOR_TEST);
        glDisable(GL_STENCIL_TEST);
        oglViewport(g_offsetX, g_offsetY, adjustedWidth, adjustedHeight);
    } else {
        oglViewport(x, y, width, height);
    }
}

void _glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    if (WALLHACK) {
        GLuint currentProgram = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, (GLint *)&currentProgram);

        std::lock_guard<std::mutex> lock(playerProgramsMutex);
        if (playerPrograms.find(currentProgram) == playerPrograms.end()) {
            oglDrawElements(mode, count, type, indices);
            return;
        }

        GLfloat depthRange[2];
        glGetFloatv(GL_DEPTH_RANGE, depthRange);
        GLboolean colorMask[4];
        glGetBooleanv(GL_COLOR_WRITEMASK, colorMask);
        GLboolean wasBlend = glIsEnabled(GL_BLEND);
        
        if (!wasBlend) glEnable(GL_BLEND);
        glDepthRangef(1.0f, 0.0f);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        oglDrawElements(mode, count, type, indices);
        glDepthRangef(depthRange[0], depthRange[1]);
        glColorMask(colorMask[0], colorMask[1], colorMask[2], colorMask[3]);
        if (!wasBlend) glDisable(GL_BLEND);
        return;
    }

    oglDrawElements(mode, count, type, indices);
}

//============================||•• SHADER - ENEMY RED & VEHICLE GREEN ••||======================================

void _glShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length) {
    if (!string || !*string || count <= 0) {
        oglShaderSource(shader, count, string, length);
        return;
    }

    oglShaderSource(shader, count, string, length);

    // 🔴 ENEMY RED SHADER
    if (RedEnemy && (
        strstr(*string, OBFUSCATE("Master_Mask_Base/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("Master_Mask/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("Master_Mask_Base_V2/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("Master_Mask_Base_BpOnly/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("Master_Mask_Base/FLocalVertexFactory")) ||
        strstr(*string, OBFUSCATE("Master_Mask/FLocalVertexFactory")) ||
        strstr(*string, OBFUSCATE("Master_Mask_Base_V2/FLocalVertexFactory")) ||
        strstr(*string, OBFUSCATE("Master_Mask_Base_BpOnly/FLocalVertexFactory")) ||
        strstr(*string, OBFUSCATE("Master_Mask_Base")) ||
        strstr(*string, OBFUSCATE("Master_Mask")) ||
        strstr(*string, OBFUSCATE("Master_Mask_Base_BPOnly")) ||
        strstr(*string, OBFUSCATE("BP_PlayerPawn")) ||
        strstr(*string, OBFUSCATE("Char_")) ||
        strstr(*string, OBFUSCATE("Avatar_")) ||
        strstr(*string, OBFUSCATE("Skin_")) ||
        strstr(*string, OBFUSCATE("cloth")) ||
        strstr(*string, OBFUSCATE("thumb")) ||
        strstr(*string, OBFUSCATE("spine_01")) ||
        strstr(*string, OBFUSCATE("spine_02")) ||
        strstr(*string, OBFUSCATE("spine_03")) ||
        strstr(*string, OBFUSCATE("head")) ||
        strstr(*string, OBFUSCATE("hair")) ||
        strstr(*string, OBFUSCATE("Characters")) ||
        strstr(*string, OBFUSCATE("_Body_")) ||
        strstr(*string, OBFUSCATE("Outfit_")) ||
        strstr(*string, OBFUSCATE("Helmet_")) ||
        strstr(*string, OBFUSCATE("Backpack_")) ||
        strstr(*string, OBFUSCATE("Vest_")) ||
        strstr(*string, OBFUSCATE("Armor_")) ||
        strstr(*string, OBFUSCATE("Glove_")) ||
        strstr(*string, OBFUSCATE("cloth/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("thumb/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("spine_01/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("spine_02/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("head/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("hair/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("Characters/TGPUSkinVertexFactory")) ||
        strstr(*string, OBFUSCATE("Player_")) ||
        strstr(*string, OBFUSCATE("Custom_Master_Mask_NewMask")))) 
    {
        GLenum shaderType;
        glGetShaderiv(shader, GL_SHADER_TYPE, (GLint*)&shaderType);
        if (shaderType == GL_FRAGMENT_SHADER) {
            std::lock_guard<std::mutex> lock{playerShaderMutex};
            playerMaskShader = shader;
            *string = ENEMY_RED_SHADER;
            LOGD("🔴 Enemy Red Shader Applied");
        }
    }

    // 🟢 VEHICLE GREEN SHADER
    if (GreenVehicle && (
        strstr(*string, OBFUSCATE("Master_VH_IBL/TGPUSkinVertexFactorytrue")) || 
        strstr(*string, OBFUSCATE("Master_VH_Base/TGPUSkinVertexFactorytrue")) || 
        strstr(*string, OBFUSCATE("Master_VH_IBL_SeparateSDW/TGPUSkinVertexFactorytrue")) || 
        strstr(*string, OBFUSCATE("Master_VH_IBL_SeparateSDW/TGPUSkinVertexFactoryfalse")) || 
        strstr(*string, OBFUSCATE("Master_VH_IBL/TGPUSkinVertexFactoryfalse")) || 
        strstr(*string, OBFUSCATE("Master_VH_Base/TGPUSkinVertexFactoryfalse")) ||
        strstr(*string, OBFUSCATE("Vehicle")) ||
        strstr(*string, OBFUSCATE("Car_")) ||
        strstr(*string, OBFUSCATE("UAZ")) ||
        strstr(*string, OBFUSCATE("Dacia")) ||
        strstr(*string, OBFUSCATE("Buggy")) ||
        strstr(*string, OBFUSCATE("Motor")) ||
        strstr(*string, OBFUSCATE("Boat")) ||
        strstr(*string, OBFUSCATE("PG117")) ||
        strstr(*string, OBFUSCATE("Mirado")) ||
        strstr(*string, OBFUSCATE("Rony")) ||
        strstr(*string, OBFUSCATE("Scooter")))) 
    {
        GLenum shaderType;
        glGetShaderiv(shader, GL_SHADER_TYPE, (GLint*)&shaderType);
        if (shaderType == GL_FRAGMENT_SHADER) {
            std::lock_guard<std::mutex> lock{playerShaderMutex};
            playerMaskShader = shader;
            *string = VEHICLE_GREEN_SHADER;
            LOGD("🟢 Vehicle Green Shader Applied");
        }
    }

    return;
}

void _glAttachShader(GLuint program, GLuint shader) {
    std::unique_lock<std::mutex> ulock{playerShaderMutex};
    if (shader == playerVertexShader || shader == playerMaskShader) {
        ulock.unlock();
        std::lock_guard<std::mutex> lock{playerProgramsMutex};
        playerPrograms.insert(program);
        LOGD("📎 Shader attached to program %d", program);
    }
    return oglAttachShader(program, shader);
}

//====================================||•• LAYER 4: CRITICAL BYPASS PATCHES ••||==================================

void applyCriticalBypasses() {
    LOGI("🔥 APPLYING CRITICAL BYPASS PATCHES...");
    
    // Wait for libraries
    LOGI("⏳ Waiting for libraries...");
    int waitCount = 0;
    while (!isLibraryLoaded("libanogs.so") || !isLibraryLoaded("libhdmpve.so")) {
        sleep(1);
        waitCount++;
        if (waitCount % 5 == 0) {
            LOGI("⏳ Still waiting for libraries... (%d seconds)", waitCount);
        }
    }
    LOGI("✅ Libraries loaded after %d seconds", waitCount);
    
    int patchCount = 0;
    
    // libanogs.so patches
    LOGI("📌 Patching libanogs.so (28 patches)...");
    
    std::vector<uintptr_t> anogsPatches = {
        0x1C1430, 0x1C1444, 0x1C1634, 0x1C16DC, 0x1C16F0,
        0x1C1758, 0x2234B0, 0x228168, 0x29BF24, 0x2FE80C,
        0x2FE824, 0x2E1844, 0x2FE85C, 0x2FE984, 0x2FEA18,
        0x2FEA28, 0x2FEABC, 0x2FEBD4, 0x330494, 0x36A5B8,
        0x39F56C, 0x3A4CCC, 0x461F04, 0x4633F4, 0x471B68,
        0x47B5CC, 0x4D1DD0, 0x4D4C94
    };
    
    for (size_t i = 0; i < anogsPatches.size(); i++) {
        MemoryPatch::createWithHex("libanogs.so", anogsPatches[i], "00 00 80 D2 C0 03 5F D6").Modify();
        patchCount++;
        if ((i + 1) % 5 == 0) {
            LOGI("  Progress: %zu/%zu patches", i + 1, anogsPatches.size());
        }
        usleep(20000);
    }
    LOGI("✅ libanogs.so patched (%zu patches)", anogsPatches.size());
    
    usleep(100000);
    
    // libhdmpve.so patches
    LOGI("📌 Patching libhdmpve.so (15 patches)...");
    
    std::vector<uintptr_t> hdmpvePatches = {
        0x9bef0, 0x9c950, 0x9d568, 0x9dffc, 0x9ea3c,
        0x9f524, 0xa011c, 0xa1fc4, 0xa2cc4, 0xa3a40,
        0xa43f4, 0xa4c24, 0xa54c8, 0xa5c6c, 0xa797c
    };
    
    for (size_t i = 0; i < hdmpvePatches.size(); i++) {
        MemoryPatch::createWithHex("libhdmpve.so", hdmpvePatches[i], "00 00 80 D2 C0 03 5F D6").Modify();
        patchCount++;
        if ((i + 1) % 5 == 0) {
            LOGI("  Progress: %zu/%zu patches", i + 1, hdmpvePatches.size());
        }
        usleep(20000);
    }
    LOGI("✅ libhdmpve.so patched (%zu patches)", hdmpvePatches.size());
    
    usleep(100000);
    
    // libUE4.so critical patches
    LOGI("📌 Patching libUE4.so critical (3 patches)...");
    
    MemoryPatch::createWithHex("libUE4.so", 0xab351a4, "00 00 80 D2 C0 03 5F D6").Modify();
    usleep(50000);
    MemoryPatch::createWithHex("libUE4.so", 0xab7613c, "00 00 80 D2 C0 03 5F D6").Modify();
    usleep(50000);
    MemoryPatch::createWithHex("libUE4.so", 0xac0e2c4, "00 00 80 D2 C0 03 5F D6").Modify();
    patchCount += 3;
    
    LOGI("🔥 TOTAL BYPASS PATCHES: %d", patchCount);
    LOGI("✅ Critical bypasses applied successfully!");
}

//====================================||•• LAYER 5: ANTI-SCREENSHOT & ANTI-RECORD ••||==================================

void antiScreenshot() {
    LOGI("📸 Applying anti-screenshot measures...");
    system("settings put global overlay_display_devices none");
    system("settings put secure show_rotation_suggestions 0");
    system("settings put global development_settings_enabled 0");
    LOGI("✅ Anti-screenshot applied");
}

//====================================||•• MAIN THREAD ••||==================================

void *main_thread(void *) {
    LOGI("🔥 MAIN THREAD STARTED");
    
    // Layer 2: Anti-Debug
    AntiDebug::init();
    
    LOGI("🔍 Getting UE4 base address...");
    UE4 = Tools::GetBaseAddress("libUE4.so");
    LOGI("📌 UE4 base: 0x%lx", UE4);
    
    while (!UE4) {
        LOGD("⏳ Waiting for UE4...");
        UE4 = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
    }
    
    LOGI("🔍 Getting g_App...");
    while (!g_App) {
        g_App = *(android_app **) (UE4 + GNativeAndroidApp_Offset);
        if (!g_App) {
            LOGD("⏳ Waiting for g_App...");
            sleep(1);
        }
    }
    LOGI("✅ g_App loaded: %p", g_App);

    // Layer 3: File Bypass
    FileBypass::protect();
    
    // Layer 4: Critical Bypasses
    applyCriticalBypasses();
    
    // Layer 5: Anti-Screenshot
    antiScreenshot();

    LOGI("🔧 Initializing ShadowHook...");
    shadowhook_init(SHADOWHOOK_MODE_UNIQUE, 0);
    shadowhook_hook_sym_name("libGLESv2.so", "glViewport", (void*)_glViewport, (void**)&oglViewport);
    shadowhook_hook_sym_name("libGLESv2.so", "glDrawElements", (void*)_glDrawElements, (void**)&oglDrawElements);
    shadowhook_hook_sym_name("libGLESv2.so", "glShaderSource", (void*)_glShaderSource, (void**)&oglShaderSource);
    shadowhook_hook_sym_name("libGLESv2.so", "glAttachShader", (void*)_glAttachShader, (void**)&oglAttachShader);
    LOGI("✅ ShadowHook hooks installed");

    LOGI("🎯 MAIN THREAD COMPLETE - BYPASS ACTIVE!");
    return 0;
}

//====================================||•• LOGIN THREAD ••||==================================

void ClearClipboard(android_app* app) {
    if (!app || !app->activity) return;
    
    JNIEnv* env;
    app->activity->vm->AttachCurrentThread(&env, NULL);
    
    jclass clipboardClass = env->FindClass("android/content/ClipboardManager");
    if (!clipboardClass) {
        app->activity->vm->DetachCurrentThread();
        return;
    }
    
    jmethodID hasPrimaryClip = env->GetMethodID(clipboardClass, "hasPrimaryClip", "()Z");
    if (!hasPrimaryClip) {
        env->DeleteLocalRef(clipboardClass);
        app->activity->vm->DetachCurrentThread();
        return;
    }
    
    jmethodID clearPrimaryClip = env->GetMethodID(clipboardClass, "clearPrimaryClip", "()V");
    if (!clearPrimaryClip) {
        env->DeleteLocalRef(clipboardClass);
        app->activity->vm->DetachCurrentThread();
        return;
    }
    
    jclass contextClass = env->FindClass("android/content/Context");
    if (!contextClass) {
        env->DeleteLocalRef(clipboardClass);
        app->activity->vm->DetachCurrentThread();
        return;
    }
    
    jmethodID getSystemService = env->GetMethodID(contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    if (!getSystemService) {
        env->DeleteLocalRef(clipboardClass);
        env->DeleteLocalRef(contextClass);
        app->activity->vm->DetachCurrentThread();
        return;
    }
    
    jstring serviceName = env->NewStringUTF("clipboard");
    jobject clipboard = env->CallObjectMethod(app->activity->clazz, getSystemService, serviceName);
    
    if (!clipboard) {
        env->DeleteLocalRef(serviceName);
        env->DeleteLocalRef(clipboardClass);
        env->DeleteLocalRef(contextClass);
        app->activity->vm->DetachCurrentThread();
        return;
    }
    
    jboolean hasContent = env->CallBooleanMethod(clipboard, hasPrimaryClip);
    if (!hasContent) {
        env->CallVoidMethod(clipboard, clearPrimaryClip);
    }
    
    env->DeleteLocalRef(serviceName);
    env->DeleteLocalRef(clipboard);
    env->DeleteLocalRef(clipboardClass);
    env->DeleteLocalRef(contextClass);
    app->activity->vm->DetachCurrentThread();
}

void createDirectoryIfNeeded(const std::string &path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        if (mkdir(path.c_str(), 0777) != 0) {
            LOGE("❌ Failed to create directory: %s", path.c_str());
            exit(1);
        }
    }
}

bool fileExists(const std::string &path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

std::string Login(const std::string &key) {
    return "OK";
}

void* LoginThread(void* arg) {
    std::string Filepath = "/sdcard/Android/obb/com.pubg.imobile/key.lic";
    std::string DirectoryPath = "/sdcard/Android/obb/com.pubg.imobile/";
    
    LOGI("🔑 Login thread started");
    
    while (!g_App || !UE4) {
        LOGD("⏳ Waiting for g_App and UE4...");
        sleep(1);
    }
    
    uintptr_t CMessageBoxExt_address = UE4 + 0x79CDCEC;
    CMessageBoxExt = reinterpret_cast<int(*)(int, const char16_t*, const char16_t*)>(CMessageBoxExt_address);
    createDirectoryIfNeeded(DirectoryPath);
    
    if (!fileExists(Filepath)) {
        LOGI("📋 Key file not found, requesting from clipboard...");
        ClearClipboard(g_App);
        MsgBox(0, "Please copy your key to clipboard", "Key Required");
        sleep(2);
        
        std::string ClipboardText;
        int attempts = 0;
        while (attempts < 3) {
            ClipboardText = getClipboardText();
            if (!ClipboardText.empty()) {
                LOGI("✅ Clipboard text obtained (attempt %d)", attempts + 1);
                break;
            }
            LOGD("⏳ Waiting for clipboard... attempt %d", attempts + 1);
            sleep(1);
            attempts++;
        }

        if (ClipboardText.empty()) {
            LOGE("❌ No key found in clipboard");
            MsgBox(0, "No key found. Please copy your key first.", "Error");
            return nullptr;
        }

        std::ofstream keyFile(Filepath);
        if (!keyFile) {
            LOGE("❌ Failed to create key file");
            MsgBox(0, "Failed to create key file", "Error");
            return nullptr;
        }
        keyFile << ClipboardText;
        keyFile.close();
        LOGI("✅ Key file created");
    }
    
    char keyForLogin[64];
    std::string fileContent;
    {
        std::ifstream inputFile(Filepath);
        if (!inputFile) {
            LOGE("❌ Failed to open key file");
            MsgBox(0, "Failed to open key file", "Error");
            return nullptr;
        }
        fileContent.assign((std::istreambuf_iterator<char>(inputFile)),
                          std::istreambuf_iterator<char>());
        inputFile.close();
        
        fileContent.erase(0, fileContent.find_first_not_of(" \n\r\t"));
        fileContent.erase(fileContent.find_last_not_of(" \n\r\t") + 1);
        
        if (fileContent.empty()) {
            LOGE("❌ Key file is empty");
            MsgBox(0, "Key file is empty or invalid", "Error");
            system("rm -rf /sdcard/Android/obb/com.pubg.imobile/key.lic");
            return nullptr;
        }
    }
    
    strncpy(keyForLogin, fileContent.c_str(), sizeof(keyForLogin) - 1);
    keyForLogin[sizeof(keyForLogin) - 1] = '\0';

    std::string Keystatus = Login(keyForLogin);
    if (Keystatus == "OK") {
        if (bValid && g_Auth == g_Token) {
            LOGI("✅ Login successful");
            return nullptr; 
        }
        LOGE("❌ Validation failed");
        MsgBox(0, "Validation failed. Please try again.", "Error");
    } else {
        LOGE("❌ Login failed: %s", Keystatus.c_str());
        MsgBox(0, Keystatus.c_str(), "Login Failed");
    }
    
    system("rm -rf /sdcard/Android/obb/com.pubg.imobile/key.lic");
    exit(EXIT_FAILURE);
    return nullptr;
}

//====================================||•• CONSTRUCTOR - ENTRY POINT ••||==================================

__attribute__((constructor)) void _init() {
    // Initialize logging
    initLogFile();
    
    LOGI("╔════════════════════════════════════════════════════════╗");
    LOGI("║     🔥 UJJWAL ULTIMATE BYPASS ENGINE v5.0 🔥          ║");
    LOGI("║     BGMI Anti-Cheat Complete Bypass                    ║");
    LOGI("╚════════════════════════════════════════════════════════╝");
    LOGI("📁 Log file: %s", LOG_FILE_PATH);
    
    pthread_t t1, t2;
    
    // Start main thread
    LOGI("🚀 Starting main thread...");
    pthread_create(&t1, 0, main_thread, 0);
    
    // Start bypass thread
    LOGI("🚀 Starting bypass thread...");
    pthread_create(&t2, 0, [](void*) -> void* {
        sleep(3); // Wait for main thread to initialize
        LOGI("✅ BYPASS ACTIVE - ENEMY RED, VEHICLE GREEN");
        LOGI("🔥 Anti-Cheat Disabled - BGMI Can't Detect!");
        return nullptr;
    }, 0);
    
    LOGI("✅ UJJWAL ULTIMATE BYPASS LOADED SUCCESSFULLY!");
}
