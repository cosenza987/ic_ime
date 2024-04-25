package com.example.pokemon;

import java.io.*;
import java.sql.SQLException;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;
import java.util.List;
import java.util.ArrayList;

@WebServlet(name = "Servlet2", value = "/servlet2")
public class Servlet2 extends HttpServlet {
    private String message;

    public void init() {
        message = "initializing servlet2";
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        PessoaDAO op = null;
        Pessoa ps = null;

        try {
            op = new PessoaDAO();
            ps = op.search(username);
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

        if(ps == null) {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
        } else if(ps.getPassword().equals(password)) {
            response.setStatus(HttpServletResponse.SC_OK);
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }

    public void destroy() {
    }
}