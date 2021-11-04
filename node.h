class node
{
    public:
        node();
        node(const node &);
        node(std::pair<team *, team *>);
        ~node();

        node & operator = (const node &);

        void set_left(node *);
        void set_right(node *);
        void set_pair(team *, team *);

        node *& get_left();
        node *& get_right();
        const std::pair<team *, team *> & get_pair() const;

    private:
        std::pair<team *, team *> spot;
        node * left;
        node * right;

        void copy_node(const node &);
};