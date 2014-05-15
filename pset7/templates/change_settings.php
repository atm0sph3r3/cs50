<h3>Change Password</h3>
<form action="settings.php" method="POST">
    <fieldset>
        <div>
            <label for="current">Current Password: </label>
            <input type="password" name="current" id="current" maxlength="25" size="25">
        </div>
        <div>
            <label for="new">New Password: </label>
            <input type="password" name="new" id="new" maxlength="25" size="25">
        </div>
        <div>
            <label for="confirm">Confirm Password: </label>
            <input type="password" name="confirm" id="confirm" maxlength="25" size="25">
        </div>
        <div>
            <input type="submit">
            <input type="reset">
        </div>
    </fieldset>
</form>