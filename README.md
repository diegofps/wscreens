# What's this?

This is a simple screenshot application

# How to install 

```bash
git clone https://github.com/diegofps/wscreens.git
cd wscreens
mkdir build
cd build
qmake ..
make
cp ./wscreen ~/.local/bin
```

# Using it

```bash
# Capture the entire screen, each screen on its own file
# By convention, each frame will be sufixed with _<FRAME_ID>_full.png
wscreen -f

# Capture current window
# By convention, the window will be sufixed with _window.png
wscreen -w

# Customizing the prefix
# In this case, the screenshot will be saved in ~/helloWorld_<TIMESTAMP>_<FRAME_ID>_full.png
wscreen -f -o ~/helloWorld
```
