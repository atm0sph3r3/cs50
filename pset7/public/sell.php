<?php
    require("../models/account_info.php");
    require("../includes/config.php");
    
    render("sell_stock.php",array("title"=>"Sell Your Stock","results"=>generatePortfolio()));
    
    