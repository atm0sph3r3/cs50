<?php
    /**
     * @brief Controller used for selling stocks
     */
    require("../includes/config.php");
    
    $user = User::getUser();
    
    if($_SERVER["REQUEST_METHOD"] == "POST"){
        $sold = $user->sell();
        render("sold_stock.php",array("title"=>"Results of Sale", "results"=>$sold));
    } else {
        render("sell_stock.php",array("title"=>"Sell Your Stock","results"=>$user->portfolio()));
    }
    
    