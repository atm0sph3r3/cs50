<h3>Change Password</h3>
<form action="settings.php" method="POST">
    <fieldset>
        <div class="form-group">
            <input type="password" name="current" placeholder="Current Password" maxlength="25" size="25">
        </div>
        <div class="form-group">
            <input type="password" name="new" placeholder="New Password" maxlength="25" size="25">
        </div>
        <div class="form-group">
            <input type="password" name="confirm" placeholder="Confirm New Password" maxlength="25" size="25">
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Change Settings</button>
            <button type="reset" class="btn btn-default">Reset</button>
        </div>
    </fieldset>
</form>