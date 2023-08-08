import java.io.*;
import java.util.*;

public class Stack {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        stack<Integer> s = new stack<Integer>();
        int n = sc.nextInt();
        for (int i = 0; i < n; i++) {
            int x = sc.nextInt();
            s.push(x);
        }
        while (!s.isEmpty()) {
            System.out.println(s.pop());
        }
        sc.close();
    }
    static public class stack<T> {
        private T[] arr;
        private int top;
        public stack() {
            arr = (T[]) new Object [1];
            top = -1;
        }
        public void push(T item) {
            if (top == arr.length - 1) {
                resize(2 * arr.length);
            }
            arr[++top] = item;
        }
        public T pop() {
            if (isEmpty()) {
                throw new NoSuchElementException("Stack underflow");
            }
            T item = arr[top];
            arr[top--] = null;
            if (top > 0 && top == arr.length / 4) {
                resize(arr.length / 2);
            }
            return item;
        }
        public T front() {
            if (isEmpty()) {
                throw new NoSuchElementException("Stack underflow");
            }
            return arr[top];
        }
        public boolean isEmpty() {
            return top == -1;
        }
        public int size() {
            return top + 1;
        }
        private void resize(int capacity) {
            T[] copy = (T[]) new Object[capacity];
            for (int i = 0; i <= top; i++) {
                copy[i] = arr[i];
            }
            arr = copy;
        }
    }
}
