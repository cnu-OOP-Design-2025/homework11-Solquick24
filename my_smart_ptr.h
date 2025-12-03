#pragma once


template<typename T>
class my_shared_ptr {
private:
    T* ptr;
    size_t* refCount;

public:
    // 생성자
    explicit my_shared_ptr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}

    // 복사 생성자
    my_shared_ptr(const my_shared_ptr& other) : ptr(other.ptr), refCount(other.refCount) { 
        /* TODO */
        (*refCount)++; // 참조 카운트 증가
    }

    // 대입 연산자
    my_shared_ptr& operator=(const my_shared_ptr& other) {
        if (this != &other) { // 자기 자신이 아닌경우에만
            release();
            ptr = other.ptr; // 다른 포인터의 리소스 복사
            refCount = other.refCount; // 참조 카운트 복사
            (*refCount)++; // 참조 카운트 증가
        }
        return *this; // 자기 자신 반환
    }

    // 소멸자
    ~my_shared_ptr() { release(); }

    // 참조 해제
    void release() {
        if (--(*refCount) == 0) { // 더 이상 이 리소스를 참조하는 포인터가 없으면
            delete ptr;  // 실제 객체 메모리에서 해제
            delete refCount; // 참조 카운트 저장하던 메모리도 해제
        }
    }

    // 접근 연산자
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // 참조 카운트 확인
    size_t use_count() const { return *refCount; }

    // get() 기능: raw 포인터 리턴
    T* get() const { return ptr; }

    // reset() 기능: 새로운 포인터로 교체
    void reset(T* p = nullptr) {
        release();
        ptr = p;
        refCount = new size_t(1);
    }
};


template <typename T>
class my_unique_ptr {
private:
    T* ptr;
public:
    // 생성자
    explicit my_unique_ptr(T* p = nullptr) : ptr(p) {}

    // 소멸자
    ~my_unique_ptr() {
        delete ptr;
    }

    // 복사 금지
    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;

    // 이동 생성자: other가 관리하는 자원의 소유권을 가져옴 
    my_unique_ptr(my_unique_ptr&& other) noexcept: ptr(nullptr) {
        /* TODO */
        ptr = other.ptr; // this가 other의 자원을 소유 
        other.ptr = nullptr; // other는 더 이상 자원을 소유하지 않음
    }

    // 이동 대입 연산자: 기존 unique_ptr이 관리하던 자원을 해제하고, 다른 unique_ptr가 관리하는 자원의 소유권을 가져옴 
    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        if (this != &other) {
            /* TODO */
            delete ptr; // 기존에 관리하던 자원 해제
            ptr = other.ptr; // this가 other의 자원을 소유
            other.ptr = nullptr; // other는 더 이상 자원을 소유하지 않음
        }
        return *this;
    }

    // 포인터 접근
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    // get() 메서드
    T* get() const { return ptr; }

    // release() 메서드: 내부 포인터를 반환하고, ptr은 nullptr로 초기화
    T* release() {
        /* TODO */
        T* temp = ptr; // 현재 내부 포인터 temp에 저장
        ptr = nullptr; // 내부 포인터를 nullptr로 초기화
        return temp; // 내부 포인터 반환
    }

    // reset() 메서드
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};
