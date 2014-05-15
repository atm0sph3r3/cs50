<?php
require("../includes/config.php");
render("view_history.php",array("title"=>"View transaction history","results"=>$user->history()));
