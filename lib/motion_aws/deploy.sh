PROJECT_ROOT=`echo ${PWD}`
mkdir -p ${PROJECT_ROOT}/build
zip -r ${PROJECT_ROOT}/build/MotionSign.zip MotionSign.py credentials.json
cd ${VIRTUAL_ENV}/lib/python3.*/site-packages && zip -r ${PROJECT_ROOT}/build/MotionSign.zip *
