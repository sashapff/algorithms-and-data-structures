import java.io.*;
import java.util.*;

public class B {
    String fileName = "sort";

    int[] mergeSort(int[] a) {
        if (a.length == 1) {
            return a;
        }
        int[] left = new int[a.length / 2];
        int[] right = new int[a.length - a.length / 2];
        for (int i = 0; i < a.length / 2; i++) {
            left[i] = a[i];
        }
        for (int i = a.length / 2; i < a.length; i++) {
            right[i - a.length / 2] = a[i];
        }
        left = mergeSort(left);
        right = mergeSort(right);
        int l = 0;
        int r = 0;
        int cnt = 0;
        while (l < left.length && r < right.length) {
            if (left[l] < right[r]) {
                a[cnt] = left[l];
                l++;
            } else {
                a[cnt] = right[r];
                r++;
            }
            cnt++;
        }
        for (int i = l; i < left.length; i++) {
            a[cnt] = left[i];
            cnt++;
        }
        for (int i = r; i < right.length; i++) {
            a[cnt] = right[i];
            cnt++;
        }
        return a;
    }

    public void solve() throws IOException {
        int n = nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = nextInt();
        }
        a = mergeSort(a);
        for (int i = 0; i < n; i++) {
            out.print(a[i] + " ");
        }
    }

    public void run() {
        try {
            if ("".equals(fileName)) {
                br = new BufferedReader(new InputStreamReader(System.in));
                out = new PrintWriter(System.out);
            } else {
                br = new BufferedReader(new FileReader(fileName + ".in"));
                out = new PrintWriter(fileName + ".out");
            }
            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }
        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    public long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    public static void main(String[] args) throws IOException {
        Locale.setDefault(Locale.US);
        new B().run();
    }

}