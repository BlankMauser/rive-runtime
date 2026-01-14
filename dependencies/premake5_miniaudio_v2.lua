dofile('rive_build_config.lua')
local dependency = require('dependency')
miniaudio = dependency.github('rive-app/miniaudio', 'rive_changes_5')

if _OPTIONS['for_switch'] then
    return
end

project('miniaudio')
do
    kind('StaticLib')
    language('C')
    includedirs({ miniaudio })

    filter('options:for_switch')
    do
        defines({
            'MA_NO_THREADING',
            'MA_NO_DEVICE_IO',
            'MA_NO_RUNTIME_LINKING',
        })
    end
    filter({})

    filter('system:ios')
    do
        files({ 'miniaudio.m' })
    end

    filter('system:macosx', 'options:variant=maccatalyst')
    do
        files({ 'miniaudio.m' })
        compileas "Objective-C++"
    end
    
    filter('system:not ios')
    do
        files({ miniaudio .. '/miniaudio.c' })
    end
end
