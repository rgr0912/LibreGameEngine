#include <testing.h>



Testing::Testing() : OgreBites::ApplicationContext("xyz")
{

}
void Testing::locateResources()
{
    auto& rgm = Ogre::ResourceGroupManager::getSingleton();
    // load resource paths from config file
    Ogre::ConfigFile cf;
    Ogre::String resourcesPath = mFSLayer->getConfigFilePath("/home/rgr/LibreGameEngine/build/external/ogre/bin/resources.cfg");
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
    Ogre::Archive* apk = Ogre::ArchiveManager::getSingleton().load("", "APKFileSystem", true);
    cf.load(apk->open(resourcesPath));
#else

    if (Ogre::FileSystemLayer::fileExists(resourcesPath) || OGRE_PLATFORM == OGRE_PLATFORM_EMSCRIPTEN)
    {
        Ogre::LogManager::getSingleton().logMessage("Parsing '"+resourcesPath+"'");
        cf.load(resourcesPath);
    }
    else
    {
        rgm.addResourceLocation(getDefaultMediaDir(), "FileSystem", Ogre::RGN_DEFAULT);
    }

#endif

    Ogre::String sec, type, arch;
    // go through all specified resource groups
    for(auto& s : cf.getSettingsBySection()) {
        sec = s.first;
        // go through all resource paths
        for (auto& t : s.second)
        {
            type = t.first;
            arch = t.second;

            Ogre::StringUtil::trim(arch);
            if (arch.empty() || arch[0] == '.')
            {
                // resolve relative path with regards to configfile
                Ogre::String baseDir, filename;
                Ogre::StringUtil::splitFilename(resourcesPath, filename, baseDir);
                arch = baseDir + arch;
            }

            arch = Ogre::FileSystemLayer::resolveBundlePath(arch);

#if OGRE_PLATFORM != OGRE_PLATFORM_EMSCRIPTEN
            if((type == "Zip" || type == "FileSystem") && !Ogre::FileSystemLayer::fileExists(arch))
            {
                Ogre::LogManager::getSingleton().logWarning("resource location '"+arch+"' does not exist - skipping");
                continue;
            }
#endif

            rgm.addResourceLocation(arch, type, sec);
        }
    }

    if(rgm.getResourceLocationList(Ogre::RGN_INTERNAL).empty())
    {
        const auto& mediaDir = getDefaultMediaDir();
        // add default locations
        rgm.addResourceLocation(mediaDir + "/Main", "FileSystem", Ogre::RGN_INTERNAL);
#ifdef OGRE_BUILD_COMPONENT_TERRAIN
        rgm.addResourceLocation(mediaDir + "/Terrain", "FileSystem", Ogre::RGN_INTERNAL);
#endif
#ifdef OGRE_BUILD_COMPONENT_RTSHADERSYSTEM
        rgm.addResourceLocation(mediaDir + "/RTShaderLib", "FileSystem", Ogre::RGN_INTERNAL);
#endif
    }

}
void Testing::setup()
{
    OgreBites::ApplicationContext::setup();
    addInputListener(this);

    lgRoot = getRoot();
    Ogre::SceneManager* scnMgr = lgRoot->createSceneManager();

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(20, 80, 50);
    //! [lightpos]

    //! [camera]
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 140);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);
    //! [camera]

    //! [entity1]
    Ogre::Entity* ogreEntity = scnMgr->createEntity("ogrehead.mesh");

    Ogre::SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    //! [entity1node]

    //! [entity1nodeattach]
    ogreNode->attachObject(ogreEntity);
    //! [entity1nodeattach]

    //! [cameramove]
    camNode->setPosition(0, 47, 222);
    //! [cameramove]
}

int main(int argc, char **argv)
{
    Testing test;
    test.initApp();
    test.getRoot()->startRendering();
    //test.closeApp();

}