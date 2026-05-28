#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

echo -e "${GREEN}============================${NC}"
echo -e "${GREEN}Поисковый движок в Docker${NC}"
echo -e "${GREEN}============================${NC}"

build() {
    echo -e "${GREEN}Очистка старых образов...${NC}"
    docker rmi search-engine 2>/dev/null || true
    docker builder prune -f 2>/dev/null || true

    echo -e "${GREEN}Сборка Docker образа...${NC}"
    docker build --no-cache -t search-engine .
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✅ Сборка завершена успешно${NC}"
    else
        echo -e "${RED}❌ Ошибка сборки${NC}"
        exit 1
    fi
}

run_tests() {
    echo -e "${GREEN}Запуск тестов...${NC}"
    docker run --rm search-engine /app/tests/test_levenshtein
    docker run --rm search-engine /app/tests/test_document
    docker run --rm search-engine /app/tests/test_inverted_index
    docker run --rm search-engine /app/tests/test_indexer
    docker run --rm search-engine /app/tests/test_search_engine
}

run_gui() {
    echo -e "${GREEN}Запуск GUI...${NC}"
    if [[ "$OSTYPE" == "darwin"* ]]; then
        echo "Для GUI на macOS нужно установить XQuartz"
        echo "Скачай: https://www.xquartz.org/"
        echo "После установки запусти XQuartz и выполни: xhost +localhost"

        docker run --rm \
            -e DISPLAY=host.docker.internal:0 \
            -v /tmp/.X11-unix:/tmp/.X11-unix \
            -v "$(pwd)/txt_files:/app/test_docs" \
            search-engine
    else
        docker run --rm \
            -e DISPLAY=$DISPLAY \
            -v /tmp/.X11-unix:/tmp/.X11-unix \
            -v "$(pwd)/txt_files:/app/test_docs" \
            search-engine
    fi
}

run_scenarios() {
    echo -e "${GREEN}Запуск сценариев...${NC}"
    for scenario in /app/tests/scenario_*; do
        if [ -f "$scenario" ] && [ ! -d "$scenario" ]; then
            echo "----------------------------------------"
            docker run --rm search-engine "$scenario"
        fi
    done
}

case "$1" in
    build)
        build
        ;;
    test)
        build
        run_tests
        ;;
    gui)
        build
        run_gui
        ;;
    scenarios)
        build
        run_scenarios
        ;;
    all)
        build
        run_tests
        run_scenarios
        echo -e "${GREEN}✅ Готово! Для запуска GUI выполни: ./run_docker.sh gui${NC}"
        ;;
    *)
        echo "Использование: ./run_docker.sh [команда]"
        echo ""
        echo "Команды:"
        echo "  build      - только собрать образ"
        echo "  test       - собрать и запустить тесты"
        echo "  gui        - собрать и запустить GUI"
        echo "  scenarios  - собрать и запустить сценарии"
        echo "  all        - собрать, запустить тесты и сценарии"
        ;;
esac
