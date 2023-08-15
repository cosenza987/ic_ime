import java.io.*;
import java.util.*;

public class StringExercises {
    public static class str {
        String s;
        int n;
        str(String s_) {
            s = s_;
            n = s.length();
        }
        boolean is_palindrome() {
            for(int i = 0; i < n / 2; i++) {
                if(s.charAt(i) != s.charAt(n - i - 1)) return false;
            }
            return true;
        }
        void reverse() {
            String tmp = new String();
            for(int i = 0; i < n; i++) {
                tmp += s.charAt(n - i - 1);
            }
            s = tmp;
        }
        void swap_lower_upper() {
            String tmp = new String();
            for(int i = 0; i < n; i++) {
                if(s.charAt(i) >= 'a' && s.charAt(i) <= 'z') {
                    tmp += (char)('A' + s.charAt(i) - 'a');
                } else {
                    tmp += (char)('a' + s.charAt(i) - 'A');
                }
            }
            s = tmp;
        }
        void caesar(int disc) {
            disc %= 26;
            String tmp = new String();
            for(int i = 0; i < n; i++) {
                if(s.charAt(i) >= 'a' && s.charAt(i) <= 'z') {
                    tmp += (char)('a' + (s.charAt(i) - 'a' + disc + 26) % 26);
                } else {
                    tmp += (char)('A' + (s.charAt(i) - 'A' + disc + 26) % 26);
                }
            }
            s = tmp;
        }
        boolean is_anagram(String x) {
            if(x.length() != n) return false;
            int a[] = new int[150], b[] = new int[150];
            for(int i = 0; i < n; i++) {
                a[s.charAt(i) - 'A']++;
                b[x.charAt(i) - 'A']++;
            }
            for(int i = 0; i < 150; i++) {
                if(a[i] != b[i]) return false;
            }
            return true;
        }
        boolean is_pangram() {
            int cnt[] = new int[26];
            for(int i = 0; i < n; i++) {
                if(s.charAt(i) >= 'a' && s.charAt(i) <= 'z') {
                    cnt[s.charAt(i) - 'a']++;
                } else {
                    cnt[s.charAt(i) - 'A']++;
                }
            }
            for(int i = 0; i < 26; i++) {
                if(cnt[i] == 0) return false;
            }
            return true;
        }
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String x = sc.next();
        str s = new str(x);
        System.out.println("is palindrome? " + s.is_palindrome());
        s.reverse();
        System.out.println("reversed: " + s.s);
        s.reverse();
        s.swap_lower_upper();
        System.out.println("swapping upper and lower: " + s.s);
        s.swap_lower_upper();
        s.caesar(15);
        System.out.println("shifting 15 to the right " + s.s);
        s.caesar(-15);
        System.out.println("is it an anagram of 'abacaxi'? " + s.is_anagram("abacaxi"));
        System.out.println("is it a pangram? " + s.is_pangram());
        sc.close();
    }
}
