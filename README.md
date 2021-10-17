# Build Docker image
```sh
docker build -t trade-bot .
```

# Run docker container
```sh
docker run -it -v /full/path/to/project/root:/trade-bot trade-bot
```

# Attach to docker console
```sh
docker exec -it trade-bot bash
```