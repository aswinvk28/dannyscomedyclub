<div class="clearfix">
    <section class="content_block_content">
        <div id="status-messages"></div>
        <div id="performer-page-ajax">
        <?php echo $paginator; ?>
        <a name="artistes"></a>
        <div id="page-list-items-ajax">
        <?php print theme_render_template(path_to_theme() . '/layouts/performer-list-performer-view-sidebar.php', array('result' => $result )); ?>
        </div>
        <?php echo $paginator; ?>
        </div>
    </section>
</div>