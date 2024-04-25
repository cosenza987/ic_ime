package com.example.pokemon;

import com.mysql.cj.x.protobuf.MysqlxPrepare;

import java.sql.*;
import java.util.*;

public class PessoaDAO {
    Connection db;

    public PessoaDAO() throws ClassNotFoundException, SQLException {
        ConnectionFactory conn = new ConnectionFactory();
        db = conn.Connect();
        String creation = "CREATE TABLE IF NOT EXISTS pessoa (username varchar(255),email varchar(255),password varchar(255), gamecount int, wincount int);";
        PreparedStatement ps = db.prepareStatement(creation);
        ps.executeUpdate();
    }

    @Override
    @SuppressWarnings("FinalizeDeclaration")
    protected void finalize() throws SQLException, Throwable {
        try {
            db.close();
        } finally {
            super.finalize();
        }
    }

    public int insert(Pessoa p) throws SQLException {
        String queryString = "INSERT INTO pessoa (username, email, password, gamecount, wincount)";
        queryString += " VALUES (?, ?, ?, 0, 0)";
        PreparedStatement stmt = db.prepareStatement(queryString);

        stmt.setString(1, p.getUsername());
        stmt.setString(2, p.getEmail());
        stmt.setString(3, p.getPassword());

        return stmt.executeUpdate();
    }

    public Pessoa search(String username) throws SQLException {
        String queryString = "SELECT username, password FROM pessoa WHERE username=?";
        PreparedStatement stmt = db.prepareStatement(queryString);
        stmt.setString(1, username);


        Pessoa pessoa = null;

        ResultSet rs = stmt.executeQuery();
        while (rs.next()) {
            Pessoa p = new Pessoa();
            p.setUsername(rs.getString(1));
            p.setEmail(rs.getString(2));
            p.setPassword(rs.getString(3));
            p.setGameCount(rs.getInt(4));
            p.setWinCount(rs.getInt(5));
            pessoa = p;
        }

        return pessoa;
    }
}