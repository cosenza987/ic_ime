package com.example.pokemon;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Pessoa {

    private String username, email, password;

    private int winCount, gameCount;

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public int getWinCount() { return winCount; }

    public void setWinCount(int winCount) { this.winCount = winCount; }

    public int getGameCount() { return gameCount; }

    public void setGameCount(int gameCount) { this.gameCount = gameCount; }
}
