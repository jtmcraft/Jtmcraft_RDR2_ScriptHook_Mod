#include "UiNotification.h"

struct {
	alignas(8) int f_0;
	alignas(8) const char* f_1;
	alignas(8) const char* f_2;
	alignas(8) int f_3;
} notificationRightParam0;

struct {
	alignas(8) int f_0;
	alignas(8) const char* f_1;
	alignas(8) const char* f_2;
	alignas(8) int f_3;
	alignas(8) int f_4;
	alignas(8) int f_5;
	alignas(8) int f_6;
} notificationRightParam1;

struct {
	alignas(8) int p0;
	alignas(8) int p1;
	alignas(8) int p2;
	alignas(8) int p3;
} notificationTopLeftParam0;

struct {
	alignas(8) int p0;
	alignas(8) const char* p1;
} notificationTopLeftParam1;

UiNotification::UiNotification() {
	nativesWrapper = NativesWrapper();
}

void UiNotification::notificationTopLeft(char* text, int duration) {
	notificationTopLeftParam0.p0 = duration;
	notificationTopLeftParam0.p1 = 0;
	notificationTopLeftParam0.p2 = 0;
	notificationTopLeftParam0.p3 = 0;

	notificationTopLeftParam1.p0 = 0;
	notificationTopLeftParam1.p1 = nativesWrapper.literalString(text);

	UIUNK::_0x049D5C615BD38BAD((Any*)&notificationTopLeftParam0, (Any*)&notificationTopLeftParam1, 1);
}

void UiNotification::notificationRight(char* text, char* dict, char* icon, char* colour, int duration) {
	notificationRightParam0.f_0 = duration;
	notificationRightParam0.f_1 = nativesWrapper.literalString("Transaction_Feed_Sounds");
	notificationRightParam0.f_2 = nativesWrapper.literalString("Transaction_Positive");
	notificationRightParam0.f_3 = 0;

	notificationRightParam1.f_0 = 0;
	notificationRightParam1.f_1 = nativesWrapper.literalString(text);
	notificationRightParam1.f_2 = nativesWrapper.literalString(dict);;
	notificationRightParam1.f_3 = nativesWrapper.getHash(icon);
	notificationRightParam1.f_4 = 1;
	notificationRightParam1.f_5 = nativesWrapper.getHash(colour);
	notificationRightParam1.f_6 = 0;

	UIUNK::_0xB249EBCB30DD88E0((Any*)&notificationRightParam0, (Any*)&notificationRightParam1, true);
}

void UiNotification::notifyInfo() {
	notificationTopLeft("Something you should know.\nWith multiple lines.\nMaybe.", 3000);
}

void UiNotification::notifyHeadShot() {
	notificationRight("Head shot", "toast_awards_set_h", "awards_set_h_006", "COLOR_PURE_WHITE", 500);
}
