package com.example.pokemon;

import java.io.*;
import java.sql.SQLException;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;
import java.util.List;
import java.util.ArrayList;

@WebServlet(name = "Servlet", value = "/servlet")
public class Servlet extends HttpServlet {
    private String message;

    public void init() {
        message = "initializing servlet";
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("application/json");

        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String email = request.getParameter("email");

        // objeto da pessoa
        Pessoa p = new Pessoa();
        p.setUsername(username);
        p.setEmail(email);
        p.setPassword(password);

        PessoaDAO op = null;
        int result = 0;

        try {
            op = new PessoaDAO();
            result = op.insert(p);
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
        response.setStatus(200);
        response.getWriter().println(result);
    }


    public void destroy() {
    }
}