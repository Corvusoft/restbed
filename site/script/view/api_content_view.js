Application.ApiContent = Ember.View.extend({
    templateName: 'uml',
    updateTemplate: function(templateName) {
        console.log(templateName);
        var view = this;
        view.set('templateName', templateName);
        view.rerender();
    }
});
