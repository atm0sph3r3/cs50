<?php
    require("../includes/config.php");

    //Define the amont of cash to start an account at 10,000
    define("CASH",10000,false);
    
    //If form was submitted and all information is present, create a new user
    if($_SERVER["REQUEST_METHOD"] == "POST"){
        extract($_POST);
        if(isset($username) && isset($password) && isset($confirmation)){
            if($password === $confirmation){
                $result = query("INSERT INTO users (username, hash, cash) VALUES (?,?,?)",$username,crypt($password), CASH);
                if($result !== false){
                    $rows = query("SELECT last_insert_id() as id");
                    $id = $rows[0]['id'];
                    $_SESSION['id'] = $id;
                    redirect("index.php");
                } else {
                    apologize("Unable to create a user. Please try another username and continue.");
                }
            } else {
                apologize("Passwords do not match. Try again.");
            }
        } else {
            apologize("All fields must be complete before proceeding.");
        }
    } else {
        render("register_form.php", array("title"=>"Register form"));
    }
 ?>
