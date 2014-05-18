<!DOCTYPE html>

<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="/js/jquery-1.10.2.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>
        <div class="container">

            <div id="top">
                <a href="/"><img alt="C$50 Finance" src="/img/logo.gif"/></a>

   
                <? if(isset($_SESSION['id'])): ?>
                <nav id="navigation">
                    <ul>
                        <li><a href="index.php">Home</a></li>
                        <li><a href="quote.php">Search</a></li>
                        <li><a href="buy.php">Purchase Stock</a></li>
                        <li><a href="sell.php">Sell Stock</a></li>
                        <li><a href="history.php">View History</a></li>
                        <li><a href="settings.php">Account Settings</a></li>
                        <li><a href="logout.php">Logout</a></li>
                    </ul>
                </nav>
                <? endif; ?>
            </div>
            <div id="middle">
