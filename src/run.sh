make clean
docker image rm -f bodgerun/my_grep
docker image build -t bodgerun/my_grep -f Dockerfile ..
docker container run -it --rm bodgerun/my_grep
