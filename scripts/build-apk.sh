export ICON=lc.png
export PACKAGE=lostcoast
export APP_NAME="Half-Life 2: Neon Overdrive"
cd srceng-mod-launcher
git clone https://gitlab.com/LostGamer/android-sdk
export ANDROID_SDK_HOME=$PWD/android-sdk
git pull
chmod +x android/scripts/script.sh
android/scripts/script.sh
chmod +x waf
./waf configure -T release &&
./waf build
