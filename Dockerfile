FROM alpine

RUN apk add g++
RUN apk add make

COPY . /app
WORKDIR app
RUN make web
ENTRYPOINT ["./start.sh"]