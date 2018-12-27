#include "graphics.h"

int isRunning = 1;

int main(int argc, char* argv[])
{
    ContextData contextData;
    contextData.minimalGLXVersionMajor = 1;
    contextData.minimalGLXVersionMinor = 3;
    contextData.minimalGLVersionMajor = 3;
    contextData.minimalGLVersionMinor = 3;
    contextData.windowWidth = 300;
    contextData.windowHeight = 300;
    contextData.name = "Faith";

    configureOpenGL(&contextData);
    loadFunctionPointers();

    PixelBufferData pixelData;
    createTextureForDrawingBuffer(&contextData, &pixelData);
    pixelData.basicProgram = createBasicProgram();
    const unsigned pixelsSize = sizeof(unsigned) * contextData.windowHeight * contextData.windowWidth;
    pixelData.pixels = (unsigned*)malloc(pixelsSize);

    unsigned* running = pixelData.pixels;
    for(unsigned y = 0; y < contextData.windowHeight; ++y)
    {
        for (unsigned x = 0; x < contextData.windowWidth; ++x)
        {
            *running = RGBAtoUnsigned(255, 0, 0, 0);
            ++running;
        }
    }
    
    while(1)
    {        
        XEvent event;
        
        while (XPending(contextData.display))
        {
            XNextEvent(contextData.display, &event);
            switch (event.type)
            {
                case ClientMessage:
                    if (event.xclient.data.l[0] == contextData.deleteMessage)
                        isRunning = 0;
                    break;
            }
        }

        if (isRunning == 0)
        {
            break;
        }

#if 0
        glClearColor(0, 0.5, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
#endif

        drawTextureWithBufferData(&contextData, &pixelData);

        glXSwapBuffers(contextData.display, contextData.window);
        
        //sleep(1);
    }

    freeContextData(&contextData);
    freePixelData(&pixelData);
    
    return 0;
}
