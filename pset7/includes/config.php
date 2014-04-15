<?php

    /**
     * config.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Configures pages.
     */

    // display errors, warnings, and notices
    ini_set("display_errors", true);
    error_reporting(E_ALL);

    // requirements
    require("constants.php");
    require("functions.php");

    // enable sessions
    session_start();
   
    /**
     * Autoloading function
     */    
    spl_autoload_register(function($class){
        require_once("../classes/" . strtolower($class) . ".php");
    });

    // require authentication for most pages
//    if (!preg_match("{(?:login|logout|register)\.php$}", $_SERVER["PHP_SELF"]))
//    {
//        if (empty($_SESSION["id"]))
//        {
//            redirect("login");
//        }
//    }

?>
