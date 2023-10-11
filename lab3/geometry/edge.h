#ifndef EDGE_H
#define EDGE_H


template<class T>
struct Edge
{
public:
    /*brief конструктор*/
    Edge();

    /*brief конструктор*/
    Edge(const T& start, const T& end);

    /*brief конструктор*/
    Edge(const Edge<T>& other);

    /*brief оператор =*/
    Edge<T>& operator=(const Edge<T>& other);

    /*brief Получение начальной точки*/
    T getStart() const;

    /*brief Получение конечной точки*/
    T getEnd() const;

    /*brief Установка начальной точки*/
    void setStart(const T& s);

    /*brief Установка конечной точки*/
    void setEnd(const T& e);

private:
    /*brief Начальная точка*/
    T start;

    /*brief Конечная точка*/
    T end;
};


template<class T>
Edge<T>::Edge()
{
    start = T{};
    end = T{};
}

template<class T>
Edge<T>::Edge(const T& start, const T& end) : start(start), end(end) {}


template<class T>
Edge<T>::Edge(const Edge<T>& other) {
    start = other.start;
    end = other.end;
}


template<class T>
Edge<T>& Edge<T>::operator=(const Edge<T>& other) {
    if (this == &other) {
        return *this;
    }
    start = other.start;
    end = other.end;
    return *this;
}

template<class T>
T Edge<T>::getStart() const
{
    return start;
}

template<class T>
T Edge<T>::getEnd() const
{
    return end;
}

template<class T>
void Edge<T>::setStart(const T& s)
{
    start = s;
}

template<class T>
void Edge<T>::setEnd(const T& e)
{
    end = e;
}


#endif // EDGE_H
