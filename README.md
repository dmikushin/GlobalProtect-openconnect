# GPAgent: GlobalProtect Single Executable

This is an implementation of GlobalProtect as a single executable, without client-server separation.

## Features

- Similar user experience as the official client in macOS.
- Supports both SAML and non-SAML authentication modes.
- Supports automatically selecting the preferred gateway from the multiple gateways.
- Supports switching gateway from the system tray menu manually.

## Prerequisites

```
sudo apt-get install -y \
     build-essential \
     qtbase5-dev \
     libqt5websockets5-dev \
     qtwebengine5-dev \
     qttools5-dev \
     qt5keychain-dev \
     openconnect
```

## Building

```
mkdir build
cd build
cmake -G Ninja ..
cmake --build .
cmake --install .
```

## Run

Once the software is installed, you can run `gpagent` to start the UI.

## Passing the Custom Parameters to `OpenConnect` CLI

See [Configuration](https://github.com/yuezk/GlobalProtect-openconnect/wiki/Configuration)

## Display the system tray icon on Gnome 40

Install the [AppIndicator and KStatusNotifierItem Support](https://extensions.gnome.org/extension/615/appindicator-support/) extension and you will see the system tray icon (Restart the system after the installation).

<img src="https://user-images.githubusercontent.com/3297602/130831022-b93492fd-46dd-4a8e-94a4-13b5747120b7.png" />


## Troubleshooting

Run `gpagent` in the Terminal and collect the logs.

