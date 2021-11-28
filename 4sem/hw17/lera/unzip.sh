dirBuild="/rfdyn/models/build/"
verBuild="20.2m"
path="$dirBuild${verBuild}/"

cd $path
cat list.OK
dirBuild="/rfdyn/models/build/"
verBuild="20.2m"
path="$dirBuild${verBuild}/"

listBuilds= cat ${path}list.OK
echo $listBuilds


grep '[:digit:]{8}-[:digit:]{6}' ${path}list.OK