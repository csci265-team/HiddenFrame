import { type MetaFunction, type LoaderFunction, redirect } from "@remix-run/node";

import { getSession, destroySession } from "../session";

export const meta: MetaFunction = () => {
    return [
        { title: "HiddenFrame" },
        { name: "description", content: "Welcome to HiddenFrame!" },
    ];
};

export const loader: LoaderFunction = async ({ request }) => {
    const session = await getSession(request.headers.get("Cookie"));
    return redirect("/", {
        headers: {
            "Set-Cookie": await destroySession(session),
        },
    });
};

export default function Logout() {

    return (
        <></>
    );
}