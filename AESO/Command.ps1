docker build -t assembly-armv7 -f Dockerfile-AssemblyArm_v7 .
docker run --mount src=d:/User/Documents/Projects/Uni/AESO/AssemblyCode,target=/home/aeso2021/Code,type=bind -it assembly-armv7