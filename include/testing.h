#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

class Testing: public OgreBites::ApplicationContext, public OgreBites::InputListener
{
    public:
    Testing();
    void setup();
    void locateResources();
    private:
    int z;
    Ogre::Root *lgRoot;

};