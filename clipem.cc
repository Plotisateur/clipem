#define NAPI_VERSION 3
#include <windows.h>
#include <cstdlib>
#include <napi.h>

using namespace Napi;

double Estimate(int points);
void toClipboard(const std::string &s);
char* fromClipboard();

class PasteWorker : public AsyncWorker {
 public:
  PasteWorker(Function& callback)
    : AsyncWorker(callback) {}
  ~PasteWorker() {}
  std::string pasted;
  void Execute () {
    pasted = fromClipboard();
  }

  void OnOK() {
    HandleScope scope(Env());
    Callback().Call({Env().Undefined(), String::New(Env(), pasted)});
  }
};

class CopyWorker : public AsyncWorker {
 public:
  CopyWorker(Function& callback, std::string str)
    : AsyncWorker(callback), str(str) {}
  ~CopyWorker() {}

  void Execute () {
    toClipboard(str);
  }

  void OnOK() {
    HandleScope scope(Env());
    Callback().Call({Env().Undefined(), String::New(Env(), str)});
  }
  private:
  std::string str;
};

String ClipboardPaste(const CallbackInfo& info) {
	return String::New(info.Env(), fromClipboard());
}

String ClipboardCopy(const CallbackInfo& info) {
  String str = info[0].As<String>();
  toClipboard(str);
  return str;
}

char* fromClipboard() {
	OpenClipboard(NULL);

	HANDLE hData = GetClipboardData(CF_TEXT);
	char* text = (char*) hData;
	CloseClipboard();

	return text;
}

void toClipboard(const std::string &s) {
	OpenClipboard(NULL);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size()+1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

Value ClipboardPasteAsync(const CallbackInfo& info) {
  Function callback = info[0].As<Function>();
  PasteWorker* pasteWorker = new PasteWorker(callback);
  pasteWorker->Queue();

  return info.Env().Undefined();
}

Value ClipboardCopyAsync(const CallbackInfo& info) {
  std::string str = info[0].As<String>().Utf8Value();
  Function callback = info[1].As<Function>();
  CopyWorker* copyWorker = new CopyWorker(callback, str);
  copyWorker->Queue();
  return info.Env().Undefined();
}

Object Init(Env env, Object exports) {
  exports.Set(String::New(env, "copySync"), Function::New(env, ClipboardCopy));
  exports.Set(String::New(env, "copy"), Function::New(env, ClipboardCopyAsync));
  exports.Set(String::New(env, "pasteSync"), Function::New(env, ClipboardPaste));
  exports.Set(String::New(env, "paste"), Function::New(env, ClipboardPasteAsync));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init) 